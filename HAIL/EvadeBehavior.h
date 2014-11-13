#ifndef INCLUDED_AI_EvadeBehavior_H
#define INCLUDED_AI_EvadeBehavior_H

#include "SteeringBehavior.h"

class EvadeBehavior : public SteeringBehavior
{
public: 
	EvadeBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);

	SVector2 GetTargetDestination()		{ return mTargetDestination; }

private:
	SVector2 mPreviousDestination;
	SVector2 mTargetDestination;
};

#endif