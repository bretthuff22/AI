#ifndef INCLUDED_AI_CohesionBehavior_H
#define INCLUDED_AI_CohesionBehavior_H

#include "SteeringBehavior.h"

class CohesionBehavior : public SteeringBehavior
{
public: 
	CohesionBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);
};

#endif