#include "SeekBehavior.h"

#include "Agent.h"

SeekBehavior::SeekBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 SeekBehavior::Update(float deltaTime)
{
	SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();
	SVector2 desiredVelocity = Normalize(positionToDestination) * mpAgent->GetMaxSpeed();

	return desiredVelocity - mpAgent->GetVelocity();
}