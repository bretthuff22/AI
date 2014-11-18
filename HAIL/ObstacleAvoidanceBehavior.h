#ifndef INCLUDED_AI_ObstacleAvoidanceBehavior_H
#define INCLUDED_AI_ObstacleAvoidanceBehavior_H

#include "SteeringBehavior.h"

class ObstacleAvoidanceBehavior : public SteeringBehavior
{
public: 
	ObstacleAvoidanceBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
	SLineSegment GetBoundingLineLeft() const		{ return mBoundingLineLeft; }
	SLineSegment GetBoundingLineRight() const		{ return mBoundingLineRight; }

private:
	SLineSegment mBoundingLineLeft;
	SLineSegment mBoundingLineRight;
};

#endif