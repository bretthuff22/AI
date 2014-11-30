#include "ArriveBehavior.h"

#include "Agent.h"

ArriveBehavior::ArriveBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
	, mActive(true)
{

}

SVector2 ArriveBehavior::Update(float deltaTime)
{
	if (mActive)
	{
		SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();
		SVector2 posToDestNorm = Normalize(positionToDestination);

		float maxSpeed = mpAgent->GetMaxSpeed();

		SVector2 desiredVelocity = posToDestNorm * maxSpeed;

		float distSq = LengthSquared(positionToDestination);
		float velocitySq = LengthSquared(mpAgent->GetVelocity());
		float slowingRadiusSq = 160000.0f;
		float stopRadiusSq = 25.0f;

		if (distSq < velocitySq)
		{
			if (distSq < slowingRadiusSq && distSq > stopRadiusSq )
			{
				//desiredVelocity = -velocitySq/(2*sqrt(distSq));
				desiredVelocity = posToDestNorm * maxSpeed * distSq/(slowingRadiusSq*slowingRadiusSq*slowingRadiusSq*slowingRadiusSq);// * maxSpeed/(distSq*distSq);
			}
			else if (distSq <= stopRadiusSq)
			{
				mpAgent->SetPosition(mpAgent->GetDestination());
				desiredVelocity = SVector2(0.0f, 0.0f);
			}
		}
		return desiredVelocity - mpAgent->GetVelocity();
	}
	
	return SVector2(0.0f, 0.0f);

}