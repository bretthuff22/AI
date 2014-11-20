#include "CohesionBehavior.h"

#include "Agent.h"

CohesionBehavior::CohesionBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 CohesionBehavior::Update(float deltaTime)
{
	SVector2 totalPosition = SVector2(0.0f, 0.0f);
	unsigned int numNeighbors = 0;

	unsigned int size = mpAgent->GetAgents().size();
	for (unsigned int i = 0; i < size; ++i)
	{
		// STEP 0 - Find neighbors
		SVector2 position = mpAgent->GetPosition();
		SVector2 neighborPos = mpAgent->GetAgents()[i]->GetPosition();
		float dist = Distance(position, neighborPos);
		if (dist < 200.0f && dist != 0.0f) // 200 pixels
		{
			// STEP 1 - Find position of neighboring agents
			totalPosition += mpAgent->GetAgents()[i]->GetPosition();
			numNeighbors++;
		}
	}

	// STEP 2 - get average Position of neigbors
	
	SVector2 averagePosition = SVector2(0.0f, 0.0f);

	if (numNeighbors)
	{
		averagePosition = totalPosition/numNeighbors;
	}

	return Normalize(averagePosition - mpAgent->GetPosition()) * mpAgent->GetMaxSpeed() - mpAgent->GetVelocity();

}