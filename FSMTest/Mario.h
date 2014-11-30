#ifndef INCLUDED_MARIO_H
#define INCLUDED_MARIO_H

#include "HAIL.h"
#include "SGE.h"
using namespace SGE;

#include "Mushroom.h"

enum MarioState
{
	Idle,
	Move,
	Eat
};

class Mario : public Agent
{
public:
	Mario(AIWorld& aiWorld);
	~Mario();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void ChangeState(MarioState state);
	void SetArrive(bool onOff);


	std::vector<Mushroom>& GetMushrooms()	{ return mMushrooms; }
	int& GetMushroomIndex()					{ return mMushroomIndex; }

	

private:
	StateMachine<Mario> mStateMachine;
	SteeringModule mSteeringModule;

	ArriveBehavior mArrive;

	SGE_Sprite mSprite;

	std::vector<Mushroom> mMushrooms;
	int mMushroomIndex;
};

#endif