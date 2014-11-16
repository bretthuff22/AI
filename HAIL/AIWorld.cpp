#include "AIWorld.h"

AIWorld::AIWorld()
{

}

AIWorld::~AIWorld()
{

}

void AIWorld::AddObstacle(const SVector2& pos, float radius)
{
	mObstacles.push_back(SCircle(pos, radius));
}

void AIWorld::SetObstaclePos( const int index, SVector2 pos )
{
	if (index < mObstacles.size())
	{
		mObstacles[index].center = pos;
	}
}

void AIWorld::Clear()
{
	mObstacles.clear();
}


void AIWorld::Render()
{
	const int kNumObstacles = mObstacles.size();
	for (int i = 0; i < kNumObstacles; ++i)
	{
		SCircle& obstacle = mObstacles[i];
		Graphics_DebugCircle(obstacle, 0xffffff);
	}
}