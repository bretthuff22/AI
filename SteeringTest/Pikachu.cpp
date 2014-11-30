#include "Pikachu.h"

Pikachu::Pikachu(AIWorld& aiWorld)
	: Agent(aiWorld)
	, mSteerMode(Agent::SteerMode::kNONE)
	, mSteeringModule(this)
	, mSeek(this, 1.0f)
	, mFlee(this, 1.0f)
	, mArrive(this, 1.0f)
	, mPursuit(this, 1.0f)
	, mEvade(this, 1.0f)
	, mWander(this, 1.0f)
	, mInterpose(this, 1.0f)
	, mHide(this, 1.0f)
	, mPathFollowing(this, 1.0f)
	, mObstacleAvoidance(this, 1.0f)
	, mSeparation(this, 1.0f)
	, mCohesion(this, 1.0f)
	, mAlignment(this, 1.0f)
{

}
Pikachu::~Pikachu()
{

}

void Pikachu::Load()
{
	mSteeringModule.AddBehavior(&mSeek);
	mSteerMode = Agent::SteerMode::kSEEK;

	SetMaxForce(100.0f);
	SetMaxSpeed(100.0f);

	//mSprite.Load("pikachu.png");

	mSprite.Add("carrier_01.png");
	mSprite.Add("carrier_02.png");
	mSprite.Add("carrier_03.png");
	mSprite.Add("carrier_04.png");
	mSprite.Add("carrier_05.png");
	mSprite.Add("carrier_06.png");
	mSprite.Add("carrier_07.png");
	mSprite.Add("carrier_08.png");
	mSprite.Add("carrier_09.png");
	mSprite.Add("carrier_10.png");
	mSprite.Add("carrier_11.png");
	mSprite.Add("carrier_12.png");
	mSprite.Add("carrier_13.png");
	mSprite.Add("carrier_14.png");
	mSprite.Add("carrier_15.png");
	mSprite.Add("carrier_16.png");
	mSprite.Add("carrier_17.png");
	mSprite.Add("carrier_18.png");
	mSprite.Add("carrier_19.png");
	mSprite.Add("carrier_20.png");
	mSprite.Add("carrier_21.png");
	mSprite.Add("carrier_22.png");
	mSprite.Add("carrier_23.png");
	mSprite.Add("carrier_24.png");
	mSprite.Add("carrier_25.png");
	mSprite.Add("carrier_26.png");
	mSprite.Add("carrier_27.png");
	mSprite.Add("carrier_28.png");
	mSprite.Add("carrier_29.png");
	mSprite.Add("carrier_30.png");
	mSprite.Add("carrier_31.png");
	mSprite.Add("carrier_32.png");
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

void Pikachu::Render()
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

void Pikachu::SetSteerMode( Agent::SteerMode steerMode)
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

void Pikachu::AddSteerMode( Agent::SteerMode steerMode)
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

void Pikachu::AddDestinationForPathFollowing(SVector2 dest)
{ 
	mPathFollowing.AddDestination(dest); 
}

void Pikachu::ClearDestinationsForPathFollowing()
{
	mPathFollowing.Clear();
}
