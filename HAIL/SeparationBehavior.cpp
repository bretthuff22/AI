#include "SeparationBehavior.h"

#include "Agent.h"

SeparationBehavior::SeparationBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 SeparationBehavior::Update(float deltaTime)
{
	SVector2 steeringForce = SVector2(0.0f, 0.0f);
	
	const std::vector<Agent*>& agents = mpAgent->GetWorld().GetNearbyAgents(mpAgent->GetPosition());
	unsigned int numNeighbors = agents.size();
	for (unsigned int i = 0; i < numNeighbors; ++i)
	{
		SVector2 position = mpAgent->GetPosition();
		SVector2 neighborPos = agents[i]->GetPosition();
		SVector2 vectorAway = position - neighborPos;

		// STEP 2 - Normalize vector away
		vectorAway = Normalize(vectorAway);

		// STEP 3 - Divide by distance from neighbor
		//vectorAway /= dist;

		// STEP 4 - Accumulate in steering force
		steeringForce += vectorAway;
	}


	// SEEK
	//SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();
	//positionToDestination = Normalize(positionToDestination);
	//SVector2 desiredVelocity = Normalize(positionToDestination + steeringForce) * mpAgent->GetMaxSpeed();
	//SVector2 force = desiredVelocity - mpAgent->GetVelocity();

	return steeringForce * mpAgent->GetMaxSpeed() - mpAgent->GetVelocity();

}