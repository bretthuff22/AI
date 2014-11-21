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
	void AddSteerMode( Agent::SteerMode steerMode);
	
	Agent::SteerMode GetSteerMode()						const	{ return mSteerMode; }
	PursuitBehavior GetPursuitBehavior()				const	{ return mPursuit; }
	WanderBehavior GetWanderBehavior()					const	{ return mWander; }	
	InterposeBehavior GetInterposeBehavior()			const	{ return mInterpose; }
	void AddDestinationForPathFollowing(SVector2 dest);
	void ClearDestinationsForPathFollowing(); 
	PathFollowingBehavior GetPathFollowingBehavior()	const	{ return mPathFollowing; }
	ObstacleAvoidanceBehavior GetObstacleAvoidanceBehavior() const { return mObstacleAvoidance; } 

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
	PathFollowingBehavior mPathFollowing;
	ObstacleAvoidanceBehavior mObstacleAvoidance;
	SeparationBehavior mSeparation;
	CohesionBehavior mCohesion;
	AlignmentBehavior mAlignment;

	SGE_Sprite mSprite;
};

#endif