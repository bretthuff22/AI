#include "CohesionBehavior.h"

#include "Agent.h"

CohesionBehavior::CohesionBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 CohesionBehavior::Update(float deltaTime)
{
	SVector2 totalPosition = SVector2(0.0f, 0.0f);
	
	const std::vector<Agent*>& agents = mpAgent->GetWorld().GetNearbyAgents(mpAgent->GetPosition());
	unsigned int numNeighbors = agents.size();
	for (unsigned int i = 0; i < numNeighbors; ++i)
	{
		// STEP 1 - Find heading of neighboring agents
		totalPosition += agents[i]->GetPosition();
	}

	// STEP 2 - get average Position of neigbors
	
	SVector2 averagePosition = SVector2(0.0f, 0.0f);

	if (numNeighbors)
	{
		averagePosition = totalPosition/numNeighbors;
	}

	return Normalize(averagePosition - mpAgent->GetPosition()) * mpAgent->GetMaxSpeed() - mpAgent->GetVelocity();

}