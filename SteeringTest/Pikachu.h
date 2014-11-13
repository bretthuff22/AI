#ifndef INCLUDED_AI_Pikachu_H
#define INCLUDED_AI_Pikachu_H

#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

class Pikachu : public Agent
{
public: 
	Pikachu();
	~Pikachu();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void SetSteerMode( Agent::SteerMode steerMode);
	Agent::SteerMode GetSteerMode()			{ return mSteerMode; }
	PursuitBehavior GetPursuitBehavior()	{ return mPursuit; }

protected:
	Agent::SteerMode mSteerMode;
	SteeringModule mSteeringModule;
	SeekBehavior mSeek;
	FleeBehavior mFlee;
	ArriveBehavior mArrive;
	PursuitBehavior mPursuit;

	SGE_Sprite mSprite;
};

#endif