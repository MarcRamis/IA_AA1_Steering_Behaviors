#include "Agent.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
				 mass(0.01),
	             speed(0.5),
	             max_force(5),
	             max_velocity(200),
	             orientation(0),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

std::vector<Agent*> Agent::getNeighbour_flock()
{
	return neighbour_Flock;
}

std::vector<Wall*> Agent::getNeighbour_walls()
{
	return neighbour_walls;
}

void Agent::setFlock(Agent *agent)
{
	if (position != agent->position)
	{
		flock.push_back(agent);
	}
}

void Agent::setWalls(Wall* wall)
{
	walls.push_back(wall);
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::update(float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Search neighbour flock
	setNeighbourFlock(K_NEIGHBOUR_FLOCK_RADIUS);
	//setNeighbourWall(K_CONE_HALFANGLE_AGENTS,K_CONE_LENGTH_AGENTS);
	
	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);
	
	// Clean neighbour entities
	cleanNeighbourFlock();
	//cleanNeighbourWalls();
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, K_NEIGHBOUR_FLOCK_RADIUS, 0, 0, 255, 255);
		
		// RAYCAST drawing
		Vector2D velocityNorm = Vector2D(velocity.x / velocity.Length(), velocity.y / velocity.Length());
		Vector2D raycastVector = position + velocityNorm * K_RAYCAST_LENGTH;
		draw_line(TheApp::Instance()->getRenderer(), position, raycastVector, 0, 255, 0, 255);
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}
void Agent::setNeighbourFlock(const float neghbour_radius)
{
	for (Agent *agent_in_flock : flock) {

		float distance = Vector2D::Distance(position, agent_in_flock->position); // Calc distance
		if (distance < neghbour_radius) {
			neighbour_Flock.push_back(agent_in_flock);
		}
	}
}
void Agent::setNeighbourWall(const float cone_radius, const float cone_length)
{
	Vector2D velocityNorm = Vector2D(velocity.x / velocity.Length(), velocity.y / velocity.Length());
	Vector2D raycastVector = position + velocityNorm * K_RAYCAST_LENGTH;

	Vector2D intersectionPoint, normalVector;
	//bool obstacleAvoidanceCollision = false;

	for (Wall *w : walls)
	{
		if (SegmentSegmentIntersection(position, position + velocity.Normalize() * K_RAYCAST_LENGTH, 
			Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y - w->getHeight()), 
			Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y - w->getHeight())))
		{
			neighbour_walls.push_back(w);
		}
		if (SegmentSegmentIntersection(position, position + velocity.Normalize() * K_RAYCAST_LENGTH, Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y - w->getHeight()), Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y + w->getHeight())))
		{
			neighbour_walls.push_back(w);
		}
		if (SegmentSegmentIntersection(position, position + velocity.Normalize() * K_RAYCAST_LENGTH, Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y + w->getHeight()), Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y + w->getHeight())))
		{
			neighbour_walls.push_back(w);
		}
		if (SegmentSegmentIntersection(position, position + velocity.Normalize() * K_RAYCAST_LENGTH, Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y + w->getHeight()), Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y - w->getHeight())))
		{
			neighbour_walls.push_back(w);
		}
	}
	///Vector2D raycastVector = position + velocity.Normalize() * K_RAYCAST_LENGTH;
	//for (Wall *w : walls)
	//{
	//	if (IsInsideCone(Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y + w->getHeight()), position,velocity.Normalize() * cone_length, cone_radius))
	//	{
	//		neighbour_walls.push_back(w);
	//	}
	//	if (IsInsideCone(Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y + w->getHeight()), position, velocity.Normalize() * cone_length, cone_radius))
	//	{
	//		neighbour_walls.push_back(w);
	//	}
	//	if (IsInsideCone(Vector2D(w->getPosition().x + w->getWeight(), w->getPosition().y - w->getHeight()), position, velocity.Normalize() * cone_length, cone_radius))
	//	{
	//		neighbour_walls.push_back(w);
	//	}
	//	if (IsInsideCone(Vector2D(w->getPosition().x - w->getWeight(), w->getPosition().y - w->getHeight()), position, velocity.Normalize() * cone_length, cone_radius))
	//	{
	//		neighbour_walls.push_back(w);
	//	}
	//}
}
void Agent::cleanNeighbourFlock()
{
	neighbour_Flock.clear();
}
 
void Agent::cleanNeighbourWalls()
{
	neighbour_walls.clear();
}
Vector2D Agent::SteeringBehavior::GetSteeringForce(Agent* agent, float dtime)
{
	return this->calculateSteeringForce(agent, dtime);
}
