#ifndef INCLUDED_HAIL_STATEMACHINE_H
#define INCLUDED_HAIL_STATEMACHINE_H

#include "State.h"	

template <typename T>
class StateMachine
{
public: 
	StateMachine(T& owner);
	~StateMachine();

	void AddState(State<T>* newState);
	void Purge();

	void Update();
	void ChangeState(int stateIndex);

private:
	typedef std::vector<State<T>*> States;

	T& mOwner;

	States mStates;
	State<T>* mpCurrentState;
};

#include "StateMachine.inl"

#endif