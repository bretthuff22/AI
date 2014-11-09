#ifndef INCLUDED_AI_SeekBehavior_H
#define INCLUDED_AI_SeekBehavior_H

#include "SteeringBehavior.h"

class SeekBehavior : public SteeringBehavior
{
public: 
	SeekBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif