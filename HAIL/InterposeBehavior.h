#ifndef INCLUDED_AI_InterposeBehavior_H
#define INCLUDED_AI_InterposeBehavior_H

#include "SteeringBehavior.h"

class InterposeBehavior : public SteeringBehavior
{
public: 
	InterposeBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);

	SVector2 GetTargetDestination()		{ return mTargetDestination; }
	void SetDestination(SVector2 vector1, SVector2 vector2);

private:
	SVector2 mPreviousDestination;
	SVector2 mTargetDestination;
};

#endif