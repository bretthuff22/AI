#ifndef INCLUDED_AI_SeparationBehavior_H
#define INCLUDED_AI_SeparationBehavior_H

#include "SteeringBehavior.h"

class SeparationBehavior : public SteeringBehavior
{
public: 
	SeparationBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif