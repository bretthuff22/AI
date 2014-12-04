#include "WorldObject.h"



WorldObject::WorldObject()
	: mPosition(0,0)
	, mActive(false)
{

}

void WorldObject::Unload()
{
	mSprite.Unload();
}

void WorldObject::Render()
{
	if (mActive)
	{
		const float kHalfWidth = mSprite.GetWidth()*0.5f;
		const float kHalfHeight = mSprite.GetHeight()*0.5f;
		const SVector2 pos(GetPosition().x - kHalfWidth, GetPosition().y - kHalfHeight);

		mSprite.SetPosition(pos);
		mSprite.Render();
	}
}

void WorldObject::Spawn(const SVector2& pos)
{
	mPosition = pos;
	mActive = true;
}

bool WorldObject::IsActive()
{
	return mActive;
}