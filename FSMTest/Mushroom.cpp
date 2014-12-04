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

void Mushroom::Eat()
{
	mActive = false;
}
