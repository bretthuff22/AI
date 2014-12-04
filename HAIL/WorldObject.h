#ifndef INCLUDED_AI_WORLD_OBJECT_H
#define INCLUDED_AI_WORLD_OBJECT_H


#include <SGE.h>
using namespace SGE;

class WorldObject
{
public:
	WorldObject();
	~WorldObject() {};

	virtual void Load() = 0;
	void Unload();
	void Render();

	void Spawn(const SVector2& pos);
	bool IsActive();

	const SVector2& GetPosition() const { return mPosition; }

protected:
	SGE_Sprite mSprite;
	SVector2 mPosition;
	bool mActive;
};


#endif