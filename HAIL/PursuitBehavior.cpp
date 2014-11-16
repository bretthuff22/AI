#include "PursuitBehavior.h"

#include "Agent.h"

PursuitBehavior::PursuitBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
	, mPreviousDestination(-1.0f, -1.0f)
{

}

SVector2 PursuitBehavior::Update(float deltaTime)
{
	SVector2 returnForce = SVector2(0.0f, 0.0f);

	if (mPreviousDestination != SVector2(-1.0f, -1.0f))
	{
		SVector2 targetVelocity = (mpAgent->GetDestination() - mPreviousDestination)/deltaTime;
		//targetVelocity = Normalize(targetVelocity);
		float maxSpeed = mpAgent->GetMaxSpeed();

		float distFromTarget = Length(mpAgent->GetDestination() - mpAgent->GetPosition());
		float expectedTime = distFromTarget/maxSpeed;
		mTargetDestination = mpAgent->GetDestination() + targetVelocity * expectedTime;


		// SEEK
		SVector2 positionToDestination = mTargetDestination - mpAgent->GetPosition();
		SVector2 desiredVelocity = Normalize(positionToDestination) * mpAgent->GetMaxSpeed();

		returnForce = desiredVelocity - mpAgent->GetVelocity();
	}

	mPreviousDestination = mpAgent->GetDestination();

	return returnForce;
}

