#include "PriorityList.h"

PriorityList::PriorityList()
{

}

PriorityList::PriorityList(std::vector<Agent::SteeringBehavior*> _sb, std::vector<float*> _steeringPriority_K) : mySteeringsBehaviors(_sb), steeringPriority_K(_steeringPriority_K)
{

}

PriorityList::~PriorityList()
{
    for (int i = 0; i < (int)mySteeringsBehaviors.size(); i++)
    {
        delete mySteeringsBehaviors[i];
        delete steeringPriority_K[i];
    }
}

Vector2D PriorityList::calculateSteeringForce(Agent* agent, float dtime)
{

    for (int i = 0; i < mySteeringsBehaviors.size() - 1; i++)
    {
        if (mySteeringsBehaviors[i]->GetSteeringForce(agent, dtime).Length() > *steeringPriority_K[i])
        {
            return mySteeringsBehaviors[i]->GetSteeringForce(agent, dtime);
        }
    }



	return mySteeringsBehaviors[mySteeringsBehaviors.size() - 1]->GetSteeringForce(agent, dtime);
}
