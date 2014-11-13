#ifndef INCLUDED_AI_AGENT_H
#define INCLUDED_AI_AGENT_H

#include <SGE.h>
using namespace SGE;

class Agent
{
public:

	enum SteerMode
	{
		kNONE,
		kSEEK,
		kFLEE,
		kARRIVE,
		kPURSUIT,
		kEVADE
	};

	Agent();
	virtual ~Agent();

	void SetPosition(SVector2 position)					{mPosition = position;}
	void SetDestination(SVector2 destination)	{mDestination = destination;}
	void SetVelocity(SVector2 velocity)					{mVelocity = velocity;}
	void SetHeading(SVector2 heading)					{mHeading = heading;}
	void SetSide(SVector2 side)							{mSide = side;}
	void SetMaxForce(float force)						{mMaxForce = force;}
	void SetMaxSpeed(float speed)						{mMaxSpeed = speed;}

	SVector2 GetPosition()								{return mPosition;}
	SVector2 GetDestination()							{return mDestination;}
	SVector2 GetVelocity()								{return mVelocity;}
	SVector2 GetHeading()								{return mHeading;}
	SVector2 GetSide()									{return mSide;}
	float GetMaxForce()									{return mMaxForce;}
	float GetMaxSpeed()									{return mMaxSpeed;}

private:
	SVector2 mPosition;
	SVector2 mDestination;
	SVector2 mVelocity;

	SVector2 mHeading;
	SVector2 mSide;

	float mMaxForce;
	float mMaxSpeed;

};

#endif //INCLUDED_AI_Agent_H