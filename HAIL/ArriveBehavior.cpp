#include "ArriveBehavior.h"

#include "Agent.h"

ArriveBehavior::ArriveBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 ArriveBehavior::Update(float deltaTime)
{
	SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();

	SVector2 posToDestNorm = Normalize(positionToDestination);
	float maxSpeed = mpAgent->GetMaxSpeed();

	SVector2 desiredVelocity = posToDestNorm * maxSpeed;

	float distSq = LengthSquared(positionToDestination);
	float velocitySq = LengthSquared(mpAgent->GetVelocity());

	if (distSq < velocitySq)
	{
		if (distSq > 36.0f)
		{
			desiredVelocity = posToDestNorm;// * maxSpeed/(distSq*distSq);
		}
		else
		{
			mpAgent->SetPosition(mpAgent->GetDestination());
			desiredVelocity = SVector2(0.0f, 0.0f);
			//mpAgent->SetVelocity(desiredVelocity);
		}
	}

	return desiredVelocity - mpAgent->GetVelocity();
}