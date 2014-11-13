#ifndef INCLUDED_AI_PursuitBehavior_H
#define INCLUDED_AI_PursuitBehavior_H

#include "SteeringBehavior.h"

class PursuitBehavior : public SteeringBehavior
{
public: 
	PursuitBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);

	SVector2 GetTargetDestination()		{ return mTargetDestination; }

private:
	SVector2 mPreviousDestination;
	SVector2 mTargetDestination;
};

#endif