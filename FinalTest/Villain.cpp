#include "Villain.h"
#include "VillainState.h"

Villain::Villain(AIWorld& aiWorld)
	: Agent(aiWorld)
	, mSteerMode(Agent::SteerMode::kNONE)
	, mSteeringModule(this)
	, mArrive(this, 1.0f)
	, mPerceptionModule(*this)
	, mStateMachine(*this)
	, mPathPlanner(*this)
{

}
Villain::~Villain()
{

}

void Villain::Load()
{
 	mStateMachine.AddState(new IdleState());
	mStateMachine.AddState(new MoveState());
	ChangeState(Idle);

	SetAgentType(kVILLAIN);
	mPerceptionModule.SetViewDistance(200.0f);
	mPerceptionModule.SetViewAngle(kPI*0.15f);
	mPerceptionModule.SetMemorySpan(3.0f);

	mSteerMode = Agent::SteerMode::kNONE;

	SetMaxForce(100.0f);
	SetMaxSpeed(100.0f);

	mSprite.Load("villain.png");
}

void Villain::Unload()
{
	mStateMachine.Purge();

	mSprite.Unload();
}

void Villain::Update(float deltaTime)
{
	mPerceptionModule.Update(deltaTime);
	mStateMachine.Update();
	

	SVector2 force = mSteeringModule.Update(deltaTime);
	SVector2 acceleration = force / 1.0f; // should be mass 
	SetVelocity(GetVelocity() + acceleration * deltaTime);
	SVector2 vel = GetVelocity();
	vel.Truncate(GetMaxSpeed());
	SetVelocity(vel);
	SVector2 pos = GetPosition() + vel * deltaTime;

	pos = GetWorld().Wrap(pos);

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

	const float angle = atan2f(GetHeading().y, GetHeading().x) + (kPI * 2.5f);
	mSprite.SetCurrentFrame((int)(angle / (kPI * 2.0f) * 32) % 32);

	mSprite.SetPosition(pos);
	mSprite.Render();

	const float viewAngle = mPerceptionModule.GetViewAngle();
	float radius = 200.0f*atanf(viewAngle);
	SVector2 center = GetPosition() + GetHeading()*200.0f;
	SCircle circle(center, radius);
	Graphics_DebugCircle(circle, 0xffff00);
	
	Graphics_DebugLine(GetPosition(), center, 0xffff00);
}

void Villain::SetSteerMode( Agent::SteerMode steerMode)
{
	mSteeringModule.Clear();
	mSteerMode = steerMode;

	if (steerMode == kARRIVE)
	{
		mSteeringModule.AddBehavior(&mArrive);
	}
}

void Villain::AddSteerMode( Agent::SteerMode steerMode)
{
	
}

void Villain::ChangeState(VillainState state)
{
	mStateMachine.ChangeState((int)state);
}

void Villain::SetArrive(bool onOff)
{
	mArrive.SetActive(onOff);
}
