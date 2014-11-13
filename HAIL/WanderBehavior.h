#ifndef INCLUDED_AI_WanderBehavior_H
#define INCLUDED_AI_WanderBehavior_H

#include "SteeringBehavior.h"

class WanderBehavior : public SteeringBehavior
{
public: 
	WanderBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
	SVector2 GetTargetDestination()			{ return mTarget; }
	SCircle GetCircle()						{ return mCircle; }

private: 
	SCircle mCircle;
	SVector2 mTarget;
};

#endif