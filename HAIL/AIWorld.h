#ifndef INCLUDED_AI_AIWorld_H
#define INCLUDED_AI_AIWorld_H

#include <SGE.h>
#include "Agent.h"

using namespace SGE;

struct AgentFactory
{
	virtual Agent* CreateAgent(AIWorld* world, int typeID) = 0;
};

class AIWorld
{
public:
	
	typedef std::vector<SCircle> Obstacles;

	AIWorld(AgentFactory& factory, Agent::AgentType type, unsigned int numAgents, unsigned int screenWidth, unsigned int screenHeight);
	~AIWorld();

	void AddObstacle(const SVector2& pos, float radius);
	void SetObstaclePos( const int index, SVector2 pos );
	Agent* CreateAgent(int typeID);

	const std::vector<Agent*>& GetAgents() const		{ return mAgents; }
	void Clear();
	void Render();
	void RenderAgents();

	void SetScreenSize(unsigned int width, unsigned int height)		{ mWidth = width; mHeight = height;}
	void SetSteerMode(Agent::SteerMode mode);
	void AddSteerMode(Agent::SteerMode mode);
	void Update(float deltaTime);
	void SetDestination(SVector2 dest);
	void SetMaxSpeed(float speed);
	void ClearAgents();
	void UpdateNeighborQuads();

	SVector2 Wrap(SVector2 vector);


	const Obstacles& GetObstacles() const	{ return mObstacles; }
	const std::vector<Agent*>& GetNearbyAgents( SVector2 pos ) const;

private:
	AgentFactory& mFactory;

	Obstacles mObstacles;
	std::vector<Agent*> mAgents;
	std::vector<Agent*> mAgentQuads[8][8];
	std::vector<Agent*> mNearbyQuads[8][8];
	std::vector<Agent*> mNearbyAgents;
	unsigned int mWidth;
	unsigned int mHeight;

};

#endif //INCLUDED_AI_AIWorld_H