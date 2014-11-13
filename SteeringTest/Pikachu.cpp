#include "Pikachu.h"

Pikachu::Pikachu()
	: mSteerMode(Agent::SteerMode::kNONE)
	, mSteeringModule(this)
	, mSeek(this, 1.0f)
	, mFlee(this, 1.0f)
	, mArrive(this, 1.0f)
	, mPursuit(this, 1.0f)
	, mEvade(this, 1.0f)
{

}
Pikachu::~Pikachu()
{

}

void Pikachu::Load()
{
	mSteeringModule.AddBehavior(&mSeek);

	SetMaxForce(100.0f);
	SetMaxSpeed(100.0f);

	mSprite.Load("pikachu.png");
}

void Pikachu::Unload()
{
	mSprite.Unload();
}

void Pikachu::Update(float deltaTime)
{
	SVector2 force = mSteeringModule.Update(deltaTime);
	SVector2 acceleration = force / 1.0f; // should be mass
	SetVelocity(GetVelocity() + acceleration * deltaTime);
	SVector2 vel = GetVelocity();
	vel.Truncate(GetMaxSpeed());
	SetVelocity(vel);
	SVector2 pos = GetPosition() + vel * deltaTime;
	SetPosition(pos);
}

void Pikachu::Render()
{
	mSprite.SetPosition(GetPosition());
	mSprite.Render();
}

void Pikachu::SetSteerMode( Agent::SteerMode steerMode)
{
	mSteeringModule.PopBehavior();
	mSteerMode = steerMode;

	if (steerMode == kSEEK)
	{
		mSteeringModule.AddBehavior(&mSeek);
	}
	else if (steerMode == kFLEE)
	{
		mSteeringModule.AddBehavior(&mFlee);
	}
	else if (steerMode == kARRIVE)
	{
		mSteeringModule.AddBehavior(&mArrive);
	}
	else if (steerMode == kPURSUIT)
	{
		mSteeringModule.AddBehavior(&mPursuit);
	}
	else if (steerMode == kEVADE)
	{
		mSteeringModule.AddBehavior(&mEvade);
	}
}