#ifndef INCLUDED_AI_ArriveBehavior_H
#define INCLUDED_AI_ArriveBehavior_H

#include "SteeringBehavior.h"

class ArriveBehavior : public SteeringBehavior
{
public: 
	ArriveBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);

	void SetActive(bool active)		{ mActive = active; }

private:
	bool mActive;
};

#endif