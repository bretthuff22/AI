#include "AlignmentBehavior.h"

#include "Agent.h"

AlignmentBehavior::AlignmentBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 AlignmentBehavior::Update(float deltaTime)
{
	SVector2 totalHeading = SVector2(0.0f, 0.0f);
	unsigned int numNeighbors = 0;

	const std::vector<Agent*>& agents = mpAgent->GetAgents();
	unsigned int size = agents.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		// STEP 0 - Find neighbors
		SVector2 position = mpAgent->GetPosition();
		SVector2 neighborPos = agents[i]->GetPosition();
		float dist = Distance(position, neighborPos);
		if (dist < 200.0f && dist != 0.0f) // 200 pixels
		{
			// STEP 1 - Find heading of neighboring agents
			totalHeading += agents[i]->GetHeading();
			numNeighbors++;
		}
	}

	// STEP 2 - get average heading of neigbors
	
	SVector2 averageHeading = SVector2(0.0f, 0.0f);

	if (numNeighbors)
	{
		averageHeading = totalHeading/numNeighbors;
	}

	return averageHeading - mpAgent->GetHeading();

}