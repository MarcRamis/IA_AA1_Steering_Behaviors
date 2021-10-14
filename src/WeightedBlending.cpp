#include "WeightedBlending.h"

WeightedBlending::WeightedBlending()
{
}

WeightedBlending::WeightedBlending(std::vector<Agent::SteeringBehavior*> _sb, std::vector<float*> _weight) 
    : m_SB(_sb), 
    m_Weight(_weight)
{
}


WeightedBlending::~WeightedBlending()
{
    for (int i = 0; i < (int)m_SB.size(); i++)
    {
        delete m_SB[i];
        delete m_Weight[i];
    }
}

Vector2D WeightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
    Vector2D steeringForceResult;

    for (int i = 0; i < m_SB.size(); i++)
    {
        steeringForceResult += m_SB[i]->calculateSteeringForce(agent, dtime).operator*(*m_Weight[i]);
    }

    return steeringForceResult;
}

Vector2D WeightedBlending::calculateSteeringForce(std::vector<Agent::SteeringBehavior*> steeringBehaviours, std::vector<float> weight, float dtime)
{
    return Vector2D();
}
