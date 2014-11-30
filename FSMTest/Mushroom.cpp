#include "Mushroom.h"

Mushroom::Mushroom()
{

}
Mushroom::~Mushroom()
{

}

void Mushroom::Load()
{
	mSprite.Load("mushroom.png");
}
void Mushroom::Unload()
{
	mSprite.Unload();
}
void Mushroom::Render()
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

void Mushroom::Spawn(const SVector2& pos)
{
	mPosition = pos;
	mActive = true;
}
void Mushroom::Eat()
{
	mActive = false;
}
bool Mushroom::IsActive()
{
	return mActive;
}