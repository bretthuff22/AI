#ifndef INCLUDED_AI_Pikachu_H
#define INCLUDED_AI_Pikachu_H

#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

class Pikachu : public Agent
{
public: 
	Pikachu();
	~Pikachu();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

protected:
	SteeringModule mSteeringModule;
	SeekBehavior mSeek;

	SGE_Sprite mSprite;
};

#endif