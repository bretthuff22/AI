#ifndef INCLUDED_VillainSTATE_H
#define INCLUDED_VillainSTATE_H


#include "HAIL.h"
#include "Villain.h"


class IdleState : public State<Villain>
{
public:
	virtual void Enter(Villain& owner);
	virtual void Update(Villain& owner);
	virtual void Exit(Villain& owner);
};

class MoveState : public State<Villain>
{
public:
	virtual void Enter(Villain& owner);
	virtual void Update(Villain& owner);
	virtual void Exit(Villain& owner);
};


#endif
