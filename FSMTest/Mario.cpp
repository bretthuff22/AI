#include "Mario.h"
#include "MarioStates.h"

Mario::Mario(AIWorld& aiWorld)
	: Agent(aiWorld)
	, mStateMachine(*this)
	, mSteeringModule(this)
	, mArrive(this, 1.0f)
{
	mArrive.SetActive(false);
}
Mario::~Mario()
{

}

void Mario::Load()
{
	mStateMachine.AddState(new IdleState());
	mStateMachine.AddState(new MoveState());
	mStateMachine.AddState(new EatState());
	ChangeState(Idle);

	mSteeringModule.AddBehavior(&mArrive);

	SetMaxForce(100.0f);
	SetMaxSpeed(300.0f);

	mSprite.Load("mario_walk_01.png");


	///////////////////////////////////
	//mMushrooms.resize(5);

	//for (int i = 0; i < 5; ++i)
	//{
	//	mMushrooms[i].Load();
	//}

	///////////////////////////////////
}

void Mario::Unload()
{
	mStateMachine.Purge();

	mSprite.Unload();

	///////////////////////////////////
	//for (int i = 0; i < mMushrooms.size(); ++i)
	//{
	//	mMushrooms[i].Unload();
	//}

	///////////////////////////////////
}

void Mario::Update(float deltaTime)
{
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

void Mario::Render()
{
	///////////////////////////////////
	//for (int i = 0; i < mMushrooms.size(); ++i)
	//{
	//	mMushrooms[i].Render();
	//}
	///////////////////////////////////

	const float kHalfWidth = mSprite.GetWidth()*0.5f;
	const float kHalfHeight = mSprite.GetHeight()*0.5f;
	const SVector2 pos(GetPosition().x - kHalfWidth, GetPosition().y - kHalfHeight);

	mSprite.SetPosition(pos);
	mSprite.Render();
}

void Mario::ChangeState(MarioState state)
{
	mStateMachine.ChangeState((int)state);
}

void Mario::SetArrive(bool onOff)
{
	mArrive.SetActive(onOff);
}