#ifndef INCLUDED_MARIOSTATES_H
#define INCLUDED_MARIOSTATES_H


#include "HAIL.h"
#include "Mario.h"

class IdleState : public State<Mario>
{
public:
	virtual void Enter(Mario& owner);
	virtual void Update(Mario& owner);
	virtual void Exit(Mario& owner);
};

class MoveState : public State<Mario>
{
public:
	virtual void Enter(Mario& owner);
	virtual void Update(Mario& owner);
	virtual void Exit(Mario& owner);
};


class EatState : public State<Mario>
{
public:
	virtual void Enter(Mario& owner);
	virtual void Update(Mario& owner);
	virtual void Exit(Mario& owner);
};

#endif
