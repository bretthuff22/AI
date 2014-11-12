#ifndef INCLUDED_AI_FleeBehavior_H
#define INCLUDED_AI_FleeBehavior_H

#include "SteeringBehavior.h"

class FleeBehavior : public SteeringBehavior
{
public: 
	FleeBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif