#include "AIWorld.h"

AIWorld::AIWorld(AgentFactory& factory, Agent::AgentType type, unsigned int numAgents, unsigned int screenWidth, unsigned int screenHeight, int tileSize)
	: mFactory(factory)
	, mWidth(screenWidth)
	, mHeight(screenHeight)
	, mAgentQuads()
	, mObjectIndex(0)
	, mpNavGraph(nullptr)
	, mTileSize(tileSize)
{
}

AIWorld::~AIWorld()
{
	
}

void AIWorld::AddWall(const SVector2& start, const SVector2& end)
{
	mWalls.push_back(SLineSegment(start, end));
}

void AIWorld::AddObstacle(const SVector2& pos, float radius)
{
	mObstacles.push_back(SCircle(pos, radius));
}

void AIWorld::SetNavGraph(Graph& graph)
{
	mpNavGraph = &graph;
}

void AIWorld::SetObstaclePos( const int index, SVector2 pos )
{
	if (index < mObstacles.size())
	{
		mObstacles[index].center = pos;
	}
}

Agent* AIWorld::CreateAgent(int typeID)
{
	Agent* newAgent = mFactory.CreateAgent(this, typeID);
	mAgents.push_back(newAgent);
	unsigned int x = (unsigned int)newAgent->GetPosition().x * 8 / mWidth;
	unsigned int y = (unsigned int)newAgent->GetPosition().y * 8 / mHeight;

	mAgentQuads[x][y].push_back(newAgent);

	return newAgent;
}


void AIWorld::Clear()
{
	mWalls.clear();
	mObstacles.clear();

	const int kNumObjects = mObjects.size();

	for (int i = 0; i < kNumObjects; ++i)
	{
		mObjects[i]->Unload();
	}


	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->Unload();
	}

	mAgents.clear();

	for(int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			mAgentQuads[i][j].clear();
		}
	}
}

bool AIWorld::HasLOS(const SVector2& start, const SVector2& end) const
{
	SLineSegment testSegment(start, end);

	const int numWalls = mWalls.size();

	for (int i = 0; i < numWalls; ++i)
	{
		const SLineSegment& wall = mWalls[i];
		if (Intersect(testSegment, wall))
		{
			return false;
		}
	}

	const int numObstacles = mObstacles.size();

	for (int i = 0; i < numObstacles; ++i)
	{
		const SCircle& circle = mObstacles[i];
		if (Intersect(testSegment, circle))
		{
			return false;
		}
	}

	return true;
}

void AIWorld::GetClosestNode(const SVector2& pos, int& x, int& y) const
{
	x = (int)pos.x / mTileSize;
	y = (int)pos.y / mTileSize;
}

void AIWorld::Load()
{
	for (int i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->Load();
	}
}

Graph& AIWorld::GetNavGraph() const
{
	return *mpNavGraph;
}

void AIWorld::Render()
{
	const int kNumObjects = mObjects.size();

	for (int i = 0; i < kNumObjects; ++i)
	{
		mObjects[i]->Render();
	}

	const int kNumObstacles = mObstacles.size();

	for (int i = 0; i < kNumObstacles; ++i)
	{
		SCircle& obstacle = mObstacles[i];
		Graphics_DebugCircle(obstacle, 0xffffff);
	}

}

void AIWorld::RenderAgents()
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		Agent* agent = mAgents[i];
		agent->Render();
	}
}

const AgentList& AIWorld::GetAgentList() const
{
	// TODO: turn vector into list?

	return mAgentList;
}



void AIWorld::SetSteerMode(Agent::SteerMode mode)
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->SetSteerMode(mode);
	}
}

void AIWorld::AddSteerMode(Agent::SteerMode mode)
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->AddSteerMode(mode);
	}
}

void AIWorld::Update(float deltaTime)
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		Agent* agent = mAgents[i];
		agent->Update(deltaTime);
		agent->SetPosition(Wrap(agent->GetPosition()));
	}

	for(int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			mAgentQuads[i][j].clear();
		}
	}

	for (int i = 0; i < kNumAgents; ++i)
	{
		SVector2 pos = mAgents[i]->GetPosition();
		//pos.x = Max(pos.x, 0.0f);
		//pos.y = Max(pos.y, 0.0f);
		mAgentQuads[(unsigned int)pos.x * 8 / mWidth][(unsigned int)pos.y * 8 / mHeight].push_back(mAgents[i]);
	}

	UpdateNeighborQuads();
}

void AIWorld::SetDestination(SVector2 dest)
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->SetDestination(dest);
	}
}

void AIWorld::SetMaxSpeed(float speed)
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->SetMaxSpeed(speed);
	}
}

void AIWorld::ClearAgents()
{
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->SetSteerMode(Agent::SteerMode::kNONE);
	}
}

void AIWorld::UpdateNeighborQuads()
{
	for (unsigned int i = 0; i < 8; ++i)
	{
		for (unsigned int j = 0; j < 8; ++j)
		{
			mNearbyQuads[i][j].clear();
			std::vector<Agent*> nearbyAgents;

			std::vector<Agent*> homeQuad = mAgentQuads[i][j];
			for (unsigned int k = 0; k < homeQuad.size(); ++k)
			{
				nearbyAgents.push_back(homeQuad[k]);
			}

			if (j > 0)
			{
				std::vector<Agent*> northQuad = mAgentQuads[i][j-1];
				for (unsigned int k = 0; k < northQuad.size(); ++k)
				{
					nearbyAgents.push_back(northQuad[k]);
				}

				if (i > 0)
				{
					std::vector<Agent*> northWQuad = mAgentQuads[i-1][j-1];
					for (unsigned int k = 0; k < northWQuad.size(); ++k)
					{
						nearbyAgents.push_back(northWQuad[k]);
					}
				}
				if (i < 7)
				{
					std::vector<Agent*> northEQuad = mAgentQuads[i+1][j-1];
					for (unsigned int k = 0; k < northEQuad.size(); ++k)
					{
						nearbyAgents.push_back(northEQuad[k]);
					}
				}
			}
	
			if (j < 7)
			{
				std::vector<Agent*> southQuad = mAgentQuads[i][j+1];
				for (unsigned int k = 0; k < southQuad.size(); ++k)
				{
					nearbyAgents.push_back(southQuad[k]);
				}

				if (i > 0)
				{
					std::vector<Agent*> southWQuad = mAgentQuads[i-1][j+1];
					for (unsigned int k = 0; k < southWQuad.size(); ++k)
					{
						nearbyAgents.push_back(southWQuad[k]);
					}
				}
				if (i < 7)
				{
					std::vector<Agent*> southEQuad = mAgentQuads[i+1][j+1];
					for (unsigned int k = 0; k < southEQuad.size(); ++k)
					{
						nearbyAgents.push_back(southEQuad[k]);
					}
				}
			}

			if (i > 0)
			{
				std::vector<Agent*> westQuad = mAgentQuads[i-1][j];
				for (unsigned int k = 0; k < westQuad.size(); ++k)
				{
					nearbyAgents.push_back(westQuad[k]);
				}
			}

			if (i < 7)
			{
				std::vector<Agent*> eastQuad = mAgentQuads[i+1][j];
				for (unsigned int k = 0; k < eastQuad.size(); ++k)
				{
					nearbyAgents.push_back(eastQuad[k]);
				}
			}

			mNearbyQuads[i][j] = nearbyAgents;
		}
	}
}

void AIWorld::AddAgent(Agent& agent)
{
	mAgents.push_back(&agent);
}

const std::vector<Agent*>& AIWorld::GetNearbyAgents(SVector2 pos) const
{
	unsigned int x = (unsigned int)pos.x * 8 / mWidth;
	unsigned int y = (unsigned int)pos.y * 8 / mHeight;

	return mNearbyQuads[x][y];
}


SVector2 AIWorld::Wrap(SVector2 vector)
{
	while (vector.x >= mWidth)
	{
		vector.x -= mWidth;
	}

	while (vector.x < 0.0f)
	{
		vector.x += mWidth;
	}

	while (vector.y >= mHeight)
	{
		vector.y -= mHeight;
	}

	while (vector.y < 0.0f)
	{
		vector.y += mHeight;
	}

	return vector;
}

const AIWorld::Walls& AIWorld::GetWalls() const
{
	return mWalls;
}