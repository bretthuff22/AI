#ifndef INCLUDED_AI_AlignmentBehavior_H
#define INCLUDED_AI_AlignmentBehavior_H

#include "SteeringBehavior.h"

class AlignmentBehavior : public SteeringBehavior
{
public: 
	AlignmentBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif