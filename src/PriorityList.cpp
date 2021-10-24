#include "PriorityList.h"

PriorityList::PriorityList()
{

}

PriorityList::PriorityList(std::list<Agent::SteeringBehavior*> _sb) : mySteeringsBehaviors(_sb)
{

}

PriorityList::~PriorityList()
{
    mySteeringsBehaviors.clear();
}

Vector2D PriorityList::calculateSteeringForce(Agent* agent, float dtime)
{
    for (Agent::SteeringBehavior* sb : mySteeringsBehaviors)
    {
        float steeringForce = sb->GetSteeringForce(agent, dtime).Length();
        if (steeringForce > K_MAX_STEERING_FORCE)
        {
            return sb->GetSteeringForce(agent, dtime);
        }
    }
}
