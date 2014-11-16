#include "InterposeBehavior.h"

#include "Agent.h"

InterposeBehavior::InterposeBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
	, mPreviousDestination(-1.0f, -1.0f)
{
}

SVector2 InterposeBehavior::Update(float deltaTime)
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
			desiredVelocity = posToDestNorm * maxSpeed * distSq/(slowingRadiusSq*slowingRadiusSq*slowingRadiusSq*slowingRadiusSq);// * maxSpeed/(distSq*distSq);
		}
		else if (distSq <= stopRadiusSq)
		{
			mpAgent->SetPosition(mpAgent->GetDestination());
			desiredVelocity = SVector2(0.0f, 0.0f);
			//mpAgent->SetVelocity(desiredVelocity);
		}
	}
	return desiredVelocity - mpAgent->GetVelocity();
}

void InterposeBehavior::SetDestination(SVector2 vector1, SVector2 vector2)
{
	mpAgent->SetDestination((vector1 + vector2)* 0.5f);
}