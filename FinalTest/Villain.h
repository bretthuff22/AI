#ifndef INCLUDED_AI_Villain_H
#define INCLUDED_AI_Villain_H

#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

class Villain : public Agent
{
public: 
	Villain(AIWorld& aiWorld);
	~Villain();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void SetSteerMode( Agent::SteerMode steerMode);
	virtual void AddSteerMode( Agent::SteerMode steerMode);
	
	Agent::SteerMode GetSteerMode()						const	{ return mSteerMode; }
	PerceptionModule GetPerceptionModule()				const	{ return mPerceptionModule; }
	
	void ChangeState(VillainState state);
	void SetArrive(bool onOff);

	

protected:
	PerceptionModule mPerceptionModule;
	StateMachine<Villain> mStateMachine;
	PathPlanner mPathPlanner;

	Agent::SteerMode mSteerMode;
	SteeringModule mSteeringModule;
	ArriveBehavior mArrive;


	SGE_Sprite mSprite;
};

#endif