#include "EvadeBehavior.h"

#include "Agent.h"

EvadeBehavior::EvadeBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
	, mPreviousDestination(-1.0f, -1.0f)
{

}

SVector2 EvadeBehavior::Update(float deltaTime)
{
	SVector2 returnForce = SVector2(0.0f, 0.0f);

	if (mPreviousDestination != SVector2(-1.0f, -1.0f))
	{
		SVector2 targetVelocity = (mpAgent->GetDestination() - mPreviousDestination)/deltaTime;
		float maxSpeed = mpAgent->GetMaxSpeed();

		float distFromTarget = Length(mpAgent->GetDestination() - mpAgent->GetPosition());
		float expectedTime = distFromTarget/maxSpeed;
		mTargetDestination = mpAgent->GetDestination() + targetVelocity * expectedTime;


		// FLEE
		const float panicDistanceSq = maxSpeed * maxSpeed;
		if (DistanceSquared(mpAgent->GetPosition(), mpAgent->GetDestination()) > panicDistanceSq)
		{
			return SVector2( 0, 0);
		}

		SVector2 positionToDestination = mpAgent->GetPosition() - mTargetDestination;
		SVector2 desiredVelocity = Normalize(positionToDestination) * mpAgent->GetMaxSpeed();

		returnForce = desiredVelocity - mpAgent->GetVelocity();
	}

	mPreviousDestination = mpAgent->GetDestination();

	return returnForce;
}