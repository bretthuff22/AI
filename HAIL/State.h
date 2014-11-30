#ifndef INCLUDED_HAIL_STATE_H
#define INCLUDED_HAIL_STATE_H

template <typename T>
class State
{
public: 
	virtual ~State() {}

	virtual void Enter(T& owner) = 0;
	virtual void Update(T& owner) = 0;
	virtual void Exit(T& owner) = 0;
};

#endif