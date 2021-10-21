#include "PriorityList.h"

std::forward_list<Agent::SteeringBehavior*> PriorityList::MyPriorityList(std::vector<Agent::SteeringBehavior*> _steeringBehaviors)
{
    std::vector<Agent::SteeringBehavior*> tempVector;
    for (Agent::SteeringBehavior* s : _steeringBehaviors)
    {
        for (Agent::SteeringBehavior* s : _steeringBehaviors)
        {

        }
    }
    return std::forward_list<Agent::SteeringBehavior*>();
}
