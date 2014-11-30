#ifndef INCLUDED_MUSHROOM_H
#define INCLUDED_MUSHROOM_H

#include "SGE.h"
using namespace SGE;

class Mushroom
{
public: 
	Mushroom();
	~Mushroom();

	void Load();
	void Unload();
	void Render();

	void Spawn(const SVector2& pos);
	void Eat();
	bool IsActive();

	const SVector2& GetPosition() const { return mPosition; }

private:
	SGE_Sprite mSprite;
	SVector2 mPosition;
	bool mActive;
};

#endif