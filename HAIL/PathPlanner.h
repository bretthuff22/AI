#ifndef INCLUDED_AI_PATHPLANNER_H
#define INCLUDED_AI_PATHPLANNER_H

#include <SGE.h>
using namespace SGE;

#include "GraphSearch.h"

typedef std::vector<SVector2> Path;

class Agent;

class PathPlanner
{
public:
	PathPlanner(Agent& owner);
	~PathPlanner();

	void RequestPath(const SVector2& destination, IValidFunctor& IsWalkable, ICostFunctor& GetG, ICostFunctor& GetH);

	const Path& GetPath() const		{ return mPath; }

private:
	Agent& mOwner;

	Path mPath;
};


#endif