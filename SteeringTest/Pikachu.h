#ifndef INCLUDED_AI_Pikachu_H
#define INCLUDED_AI_Pikachu_H

#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

class Pikachu : public Agent
{
public: 
	Pikachu(AIWorld& aiWorld);
	~Pikachu();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void SetSteerMode( Agent::SteerMode steerMode);
	
	Agent::SteerMode GetSteerMode()				const	{ return mSteerMode; }
	PursuitBehavior GetPursuitBehavior()		const	{ return mPursuit; }
	WanderBehavior GetWanderBehavior()			const	{ return mWander; }	
	InterposeBehavior GetInterposeBehavior()	const	{ return mInterpose; }

protected:
	Agent::SteerMode mSteerMode;
	SteeringModule mSteeringModule;
	SeekBehavior mSeek;
	FleeBehavior mFlee;
	ArriveBehavior mArrive;
	PursuitBehavior mPursuit;
	EvadeBehavior mEvade;
	WanderBehavior mWander;
	InterposeBehavior mInterpose;
	HideBehavior mHide;

	SGE_Sprite mSprite;
};

#endif