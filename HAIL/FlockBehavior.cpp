#include "FlockBehavior.h"

#include "Agent.h"

FlockBehavior::FlockBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 FlockBehavior::Update(float deltaTime)
{
	const float maxSpeed = mpAgent->GetMaxSpeed();
	const float panicDistanceSq = maxSpeed*maxSpeed;
	if (DistanceSquared(mpAgent->GetPosition(), mpAgent->GetDestination()) > panicDistanceSq)
	{
		return SVector2( 0, 0);
	}

	SVector2 positionToDestination = mpAgent->GetPosition() - mpAgent->GetDestination();
	SVector2 desiredVelocity = Normalize(positionToDestination) * mpAgent->GetMaxSpeed();

	return desiredVelocity - mpAgent->GetVelocity();
}