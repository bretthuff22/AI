#include "Villain.h"

Villain::Villain(AIWorld& aiWorld)
	: Agent(aiWorld)
	, mSteerMode(Agent::SteerMode::kNONE)
	, mSteeringModule(this)
	, mArrive(this, 1.0f)
{

}
Villain::~Villain()
{

}

void Villain::Load()
{
	mSteeringModule.AddBehavior(&mArrive);
	mSteerMode = Agent::SteerMode::kSEEK;

	SetMaxForce(100.0f);
	SetMaxSpeed(100.0f);

	mSprite.Load("villain.png");
}

void Villain::Unload()
{
	mSprite.Unload();
}

void Villain::Update(float deltaTime)
{
	SVector2 force = mSteeringModule.Update(deltaTime);
	SVector2 acceleration = force / 1.0f; // should be mass 
	SetVelocity(GetVelocity() + acceleration * deltaTime);
	SVector2 vel = GetVelocity();
	vel.Truncate(GetMaxSpeed());
	SetVelocity(vel);
	SVector2 pos = GetPosition() + vel * deltaTime;

	pos = GetWorld().Wrap(pos);

	//int width = IniFile_GetInt("WinWidth", 768.0f);
	//int height = IniFile_GetInt("WinHeight", 768.0f);

	//if (pos.x < -100.0f || pos.x > width)
	//{
	//	pos.x = ((int)pos.x + width) % width;
	//}

	//if (pos.y < -100.0f || pos.y > height)
	//{
	//	pos.y = ((int)pos.y + height) % height;
	//}

	SetPosition(pos);

	if (GetVelocity().LengthSquared() > 0.005f)
	{
		SetHeading(Normalize(GetVelocity()));
		SetSide(SVector2(-GetHeading().y, GetHeading().x));
	}
	
}

void Villain::Render()
{
	const float kHalfWidth = mSprite.GetWidth()*0.5f;
	const float kHalfHeight = mSprite.GetHeight()*0.5f;
	const SVector2 pos(GetPosition().x - kHalfWidth, GetPosition().y - kHalfHeight);

	//float angle = atan2f(GetHeading().y, GetHeading().x ) + (kPI *0.5f);
	const float angle = atan2f(GetHeading().y, GetHeading().x) + (kPI * 2.5f);
	mSprite.SetCurrentFrame((int)(angle / (kPI * 2.0f) * 32) % 32);

	mSprite.SetPosition(pos);
	//mSprite.SetRotation(angle);
	mSprite.Render();
}

void Villain::SetSteerMode( Agent::SteerMode steerMode)
{
	mSteeringModule.Clear();
	mSteerMode = steerMode;
	mPathFollowing.Clear();

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
	else if (steerMode == kWANDER)
	{
		mSteeringModule.AddBehavior(&mWander);
	}
	else if (steerMode == kINTERPOSE)
	{
		mSteeringModule.AddBehavior(&mInterpose);
	}
	else if (steerMode == kHIDE)
	{
		mSteeringModule.AddBehavior(&mHide);
	}
	else if (steerMode == kPATHFOLLOWING)
	{
		mSteeringModule.AddBehavior(&mPathFollowing);
	}
	else if (steerMode == kOBSTACLEAVOIDANCE)
	{
		mSteeringModule.AddBehavior(&mObstacleAvoidance);
	}
	else if (steerMode == kSEPARATION)
	{
		mSteeringModule.AddBehavior(&mSeparation);
	}
	else if (steerMode == kCOHESION)
	{
		mSteeringModule.AddBehavior(&mCohesion);
	}
	else if (steerMode == kALIGNMENT)
	{
		mSteeringModule.AddBehavior(&mAlignment);
	}
}

void Villain::AddSteerMode( Agent::SteerMode steerMode)
{
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
	else if (steerMode == kWANDER)
	{
		mSteeringModule.AddBehavior(&mWander);
	}
	else if (steerMode == kINTERPOSE)
	{
		mSteeringModule.AddBehavior(&mInterpose);
	}
	else if (steerMode == kHIDE)
	{
		mSteeringModule.AddBehavior(&mHide);
	}
	else if (steerMode == kPATHFOLLOWING)
	{
		mSteeringModule.AddBehavior(&mPathFollowing);
	}
	else if (steerMode == kOBSTACLEAVOIDANCE)
	{
		mSteeringModule.AddBehavior(&mObstacleAvoidance);
	}
	else if (steerMode == kSEPARATION)
	{
		mSteeringModule.AddBehavior(&mSeparation);
	}
	else if (steerMode == kCOHESION)
	{
		mSteeringModule.AddBehavior(&mCohesion);
	}
	else if (steerMode == kALIGNMENT)
	{
		mSteeringModule.AddBehavior(&mAlignment);
	}
}

void Villain::AddDestinationForPathFollowing(SVector2 dest)
{ 
	mPathFollowing.AddDestination(dest); 
}

void Villain::ClearDestinationsForPathFollowing()
{
	mPathFollowing.Clear();
}
