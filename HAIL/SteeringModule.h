#ifndef INCLUDED_AI_STEERINGMODULE_H
#define INCLUDED_AI_STEERINGMODULE_H

#include <SGE.h>
using namespace SGE;

class Agent;
class SteeringBehavior;

class SteeringModule
{
public: 
	SteeringModule(Agent* pAgent);
	~SteeringModule();

	void AddBehavior(SteeringBehavior* behavior);
	void PopBehavior();
	SVector2 Update(float deltaTime);

private:
	typedef std::vector< SteeringBehavior* > SteeringBehaviors;

	Agent* mpAgent;
	SteeringBehaviors mBehaviors;
};

#endif