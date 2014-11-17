#ifndef INCLUDED_AI_PathFollowingBehavior_H
#define INCLUDED_AI_PathFollowingBehavior_H

#include "SteeringBehavior.h"

#include <list>

class PathFollowingBehavior : public SteeringBehavior
{
public: 
	PathFollowingBehavior(Agent* pAgent, float weight);

	virtual SVector2 Update(float deltaTime);

	void AddDestination(SVector2 dest)		{ mDestinations.push_back(dest); }
	void Clear()							{ mDestinations.clear(); }		

private:
	std::list<SVector2> mDestinations;
};

#endif