#include "Hero.h"

Hero::Hero(AIWorld& aiWorld)
	: Agent(aiWorld)
{

}
Hero::~Hero()
{

}

void Hero::Load()
{
	mSprite.Load("hero.png");
}

void Hero::Unload()
{
	mSprite.Unload();
}

void Hero::Update(float deltaTime)
{
	
}

void Hero::Render()
{
	const float kHalfWidth = mSprite.GetWidth()*0.5f;
	const float kHalfHeight = mSprite.GetHeight()*0.5f;
	const SVector2 pos(GetPosition().x - kHalfWidth, GetPosition().y - kHalfHeight);

	mSprite.SetPosition(pos);
	mSprite.Render();
}

void Hero::SetSteerMode( Agent::SteerMode steerMode)
{
	
}

void Hero::AddSteerMode( Agent::SteerMode steerMode)
{
	
}

