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


private:
	StateMachine<Mario> mStateMachine;
	SteeringModule mSteeringModule;

	ArriveBehavior mArrive;

	SGE_Sprite mSprite;

};

#endif