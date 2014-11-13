#include "WanderBehavior.h"

#include "Agent.h"

WanderBehavior::WanderBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{
	mCircle = SCircle(mpAgent->GetPosition(), 64.0f);
	mTarget = SVector2(mpAgent->GetPosition().x + mCircle.radius, mpAgent->GetPosition().y);
}

SVector2 WanderBehavior::Update(float deltaTime)
{
	SVector2 agentPosition = mpAgent->GetPosition();

	// STEP 0: RESET CIRCLE AND TARGET AROUND AGENT
	if (mCircle.center != SVector2(0.0f, 0.0f))
	{
		mTarget -= mCircle.center - agentPosition;
	}
	else
	{
		mTarget += agentPosition;
	}
	mCircle.center = agentPosition;

	// STEP 1: ADD SMALL RANDOM DISPLACEMENT TO TARGET
	float displacementRadius = mCircle.radius * 0.25f;
	SVector2 randomDisplacement = SVector2(RandomFloat(-displacementRadius, displacementRadius), RandomFloat(-displacementRadius, displacementRadius));
	mTarget += randomDisplacement;

	// STEP 2: PROJECT TARGET BACK TO CIRCLE
	mTarget = Normalize(mTarget - mCircle.center) * mCircle.radius + mCircle.center;

	// STEP 3: PROJECT CIRCLE IN FRONT OF AGENT
	SVector2 forwardProjection = Normalize(mpAgent->GetVelocity()) * 200.0f; // projecting 200 pixels ahead
	mCircle.center += forwardProjection;
	mTarget += forwardProjection;

	// STEP 4: SEEK
	mpAgent->SetDestination(mTarget);
	SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();
	SVector2 desiredVelocity = Normalize(positionToDestination) * mpAgent->GetMaxSpeed();

	return desiredVelocity - mpAgent->GetVelocity();
}