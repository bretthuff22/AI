#ifndef INCLUDED_AI_AIWorld_H
#define INCLUDED_AI_AIWorld_H

#include <SGE.h>

using namespace SGE;

class AIWorld
{
public:
	
	typedef std::vector<SCircle> Obstacles;

	AIWorld();
	~AIWorld();

	void AddObstacle(const SVector2& pos, float radius);
	void SetObstaclePos( const int index, SVector2 pos );
	void Clear();

	void Render();

	const Obstacles& GetObstacles() const	{ return mObstacles; }

private:
	Obstacles mObstacles;

};

#endif //INCLUDED_AI_AIWorld_H