#include "Pikachu.h"

Pikachu::Pikachu()
	: mSteerMode(Agent::SteerMode::kNONE)
	, mSteeringModule(this)
	, mSeek(this, 1.0f)
	, mFlee(this, 1.0f)
	, mArrive(this, 1.0f)
{

}
Pikachu::~Pikachu()
{

}

void Pikachu::Load()
{
	mSteeringModule.AddBehavior(&mSeek);

	SetMaxForce(100.0f);
	SetMaxSpeed(300.0f);

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
	SetPosition(GetPosition() + vel * deltaTime);
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
}