#include "WeightedBlending.h"

WeightedBlending::~WeightedBlending()
{
    for (int i = 0; i < (int)steeringBehaviours.size(); i++)
    {
        delete steeringBehaviours[i];
        delete weight[i];
    }
}

Vector2D WeightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
    Vector2D steeringForceResult;
    for (int i = 0; i < steeringBehaviours.size(); i++)
    {
        steeringForceResult += steeringBehaviours[i]->calculateSteeringForce(agent, dtime).operator*(*weight[i]); //Esto es raro pero tal vez funcione, si falla implementar nosotros el operator*
    }


    return steeringForceResult;
}

Vector2D WeightedBlending::calculateSteeringForce(std::vector<Agent::SteeringBehavior*> steeringBehaviours, std::vector<float> weight, float dtime)
{
    return Vector2D();
}
