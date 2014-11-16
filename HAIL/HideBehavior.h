#ifndef INCLUDED_AI_HideBehavior_H
#define INCLUDED_AI_HideBehavior_H

#include "SteeringBehavior.h"

class HideBehavior : public SteeringBehavior
{
public: 
	HideBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif