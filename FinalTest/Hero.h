#ifndef INCLUDED_AI_HERO_H
#define INCLUDED_AI_HERO_H

#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

class Hero : public Agent
{
public: 
	Hero(AIWorld& aiWorld);
	~Hero();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void SetSteerMode( Agent::SteerMode steerMode);
	virtual void AddSteerMode( Agent::SteerMode steerMode);
	
protected:

	SGE_Sprite mSprite;
};

#endif