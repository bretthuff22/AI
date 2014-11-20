#ifndef INCLUDED_AI_FlockBehavior_H
#define INCLUDED_AI_FlockBehavior_H

#include "SteeringBehavior.h"

class FlockBehavior : public SteeringBehavior
{
public: 
	FlockBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif