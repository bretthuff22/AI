#ifndef INCLUDED_AI_AIWorld_H
#define INCLUDED_AI_AIWorld_H

#include "HAIL.h"
#include <SGE.h>
#include "Agent.h"
#include "WorldObject.h"
#include "Graph.h"
using namespace SGE;

struct AgentFactory
{
	virtual Agent* CreateAgent(AIWorld* world, int typeID) = 0;
};

struct ObjectFactory
{
	virtual WorldObject* CreateObject(AIWorld* world, int typeID) = 0;
};

class AIWorld
{
public:
	typedef std::vector<SLineSegment> Walls;
	typedef std::vector<SCircle> Obstacles;

	AIWorld(AgentFactory& factory, Agent::AgentType type, unsigned int numAgents, unsigned int screenWidth, unsigned int screenHeight, int tileSize);
	~AIWorld();

	//void RegisterAgent(Agent* agent);
	//void UnregisterAgent(Agent* agent);

	void AddWall(const SVector2& start, const SVector2& end);
	void AddObstacle(const SVector2& pos, float radius);
	void SetNavGraph(Graph& graph);
	void SetObstaclePos( const int index, SVector2 pos );
	Agent* CreateAgent(int typeID);

	const std::vector<Agent*>& GetAgents() const		{ return mAgents; }
	void Clear();

	bool HasLOS(const SVector2& start, const SVector2& end) const;

	void GetClosestNode(const SVector2& pos, int& x, int& y) const;


	void Load();

	Graph& GetNavGraph() const;
	void Render();
	void RenderAgents();

	const AgentList& GetAgentList() const;
	void SetScreenSize(unsigned int width, unsigned int height)		{ mWidth = width; mHeight = height;}
	void SetSteerMode(Agent::SteerMode mode);
	void AddSteerMode(Agent::SteerMode mode);
	void Update(float deltaTime);
	void SetDestination(SVector2 dest);
	void SetMaxSpeed(float speed);
	void ClearAgents();
	void UpdateNeighborQuads();
	void AddAgent(Agent& agent);

	SVector2 Wrap(SVector2 vector);

	const Walls& GetWalls() const;
	const Obstacles& GetObstacles() const	{ return mObstacles; }
	const std::vector<Agent*>& GetNearbyAgents( SVector2 pos ) const;

	void AddObject(WorldObject* object)			{ mObjects.push_back(object); }
	const std::vector<WorldObject*>& GetObjects()	const	{ return mObjects; }
	int GetObjectIndex()						{ return mObjectIndex; }
	void SetObjectIndex(unsigned int index)		{ mObjectIndex = index; }

private:
	AgentList mAgentList;
	Walls mWalls;
	AgentFactory& mFactory;

	Obstacles mObstacles;
	std::vector<Agent*> mAgents;
	std::vector<WorldObject*> mObjects;
	int mObjectIndex;

	std::vector<Agent*> mAgentQuads[8][8];
	std::vector<Agent*> mNearbyQuads[8][8];
	std::vector<Agent*> mNearbyAgents;
	unsigned int mWidth;
	unsigned int mHeight;

	Graph* mpNavGraph;

	int mTileSize;
};

#endif //INCLUDED_AI_AIWorld_H