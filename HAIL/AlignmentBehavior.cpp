#include "AlignmentBehavior.h"

#include "Agent.h"

AlignmentBehavior::AlignmentBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 AlignmentBehavior::Update(float deltaTime)
{
	SVector2 totalHeading = SVector2(0.0f, 0.0f);

	const std::vector<Agent*>& agents = mpAgent->GetWorld().GetNearbyAgents(mpAgent->GetPosition());
	unsigned int numNeighbors = agents.size();
	for (unsigned int i = 0; i < numNeighbors; ++i)
	{
		// STEP 1 - Find heading of neighboring agents
		totalHeading += agents[i]->GetHeading();
	}

	// STEP 2 - get average heading of neigbors
	
	SVector2 averageHeading = SVector2(0.0f, 0.0f);

	if (numNeighbors)
	{
		averageHeading = totalHeading/numNeighbors;
	}

	return averageHeading - mpAgent->GetHeading();

}