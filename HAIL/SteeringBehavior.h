#ifndef INCLUDED_AI_STEERINGBehavior_H
#define INCLUDED_AI_STEERINGBehavior_H

#include <SGE.h>
using namespace SGE;

class Agent;

class SteeringBehavior
{
public: 
	SteeringBehavior(Agent* pAgent, float weight);
	virtual ~SteeringBehavior();

	virtual SVector2 Update(float deltaTime) = 0;

	float GetWeight() const {return mWeight;}

protected:
	Agent* mpAgent;
	float mWeight;
};

#endif