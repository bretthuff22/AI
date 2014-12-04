#ifndef INCLUDED_MUSHROOM_H
#define INCLUDED_MUSHROOM_H

#include "HAIL.h"
#include "SGE.h"
using namespace SGE;

class Mushroom : public WorldObject
{
public: 
	Mushroom();
	~Mushroom();

	virtual void Load();

	void Eat();
};

#endif