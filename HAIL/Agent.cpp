#include "Agent.h"

Agent::Agent()
	: mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mHeading(1.0f, 0.0f)
	, mSide(0.0f, 1.0f)
	, mMaxForce(0.0f)
	, mMaxSpeed(0.0f)
{

}

Agent::~Agent()
{

}