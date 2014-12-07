#include "PathPlanner.h"

#include "Agent.h"
#include "AIWorld.h"
#include "AStarSearch.h"

PathPlanner::PathPlanner(Agent& owner)
	: mOwner(owner)
{

}

PathPlanner::~PathPlanner()
{

}

void PathPlanner::RequestPath(const SVector2& destination, IValidFunctor& IsWalkable, ICostFunctor& GetG, ICostFunctor& GetH)
{
	mPath.clear();

	// If there is a clear line of sight to destination, skip search

	AIWorld& world = mOwner.GetWorld();
	if (world.HasLOS(mOwner.GetPosition(), destination))
	{
		mPath.push_back(mOwner.GetPosition());
		mPath.push_back(destination);
		return;
	}

	int startX = 0, startY = 0;
	int endX = 0, endY = 0;

	// Get the closest start and end node for our search
	world.GetClosestNode(mOwner.GetPosition(), startX, startY);
	world.GetClosestNode(destination, startX, startY);

	AStarSearch search(world.GetNavGraph(), GetG, GetH);
	search.Run(startX, startY, endX, endY);
	if (search.IsFound())
	{
		NodeList nodeList;
		search.GetPath();//search.GetPath(nodeList);

		// Build path from nodelist
		mPath.push_back(mOwner.GetPosition());
		for (auto node : nodeList)
		{
			mPath.push_back(node->position);
		}
		mPath.push_back(destination);
	}


}