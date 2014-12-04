#include "AIWorld.h"

AIWorld::AIWorld(AgentFactory& factory, Agent::AgentType type, unsigned int numAgents, unsigned int screenWidth, unsigned int screenHeight)
	: mFactory(factory)
	, mWidth(screenWidth)
	, mHeight(screenHeight)
	, mAgentQuads()
	, mObjectIndex(0)
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

void AIWorld::Load()
{
	for (int i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->Load();
	}
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

const std::vector<Agent*>& AIWorld::GetNearbyAgents(SVector2 pos) const
{
	unsigned int x = (unsigned int)pos.x * 8 / mWidth;
	unsigned int y = (unsigned int)pos.y * 8 / mHeight;

	return mNearbyQuads[x][y];

	//std::vector<Agent*> homeQuad = mAgentQuads[x][y];
	//for (unsigned int i = 0; i < homeQuad.size(); ++i)
	//{
	//	mNearbyAgents.push_back(homeQuad[i]);
	//}

	//if (y > 0)
	//{
	//	std::vector<Agent*> northQuad = mAgentQuads[x][y-1];
	//	for (unsigned int i = 0; i < northQuad.size(); ++i)
	//	{
	//		mNearbyAgents.push_back(northQuad[i]);
	//	}

	//	if (x > 0)
	//	{
	//		std::vector<Agent*> northWQuad = mAgentQuads[x-1][y-1];
	//		for (unsigned int i = 0; i < northWQuad.size(); ++i)
	//		{
	//			mNearbyAgents.push_back(northWQuad[i]);
	//		}
	//	}
	//	if (x < 7)
	//	{
	//		std::vector<Agent*> northEQuad = mAgentQuads[x+1][y-1];
	//		for (unsigned int i = 0; i < northEQuad.size(); ++i)
	//		{
	//			mNearbyAgents.push_back(northEQuad[i]);
	//		}
	//	}
	//}
	//
	//if (y < 7)
	//{
	//	std::vector<Agent*> southQuad = mAgentQuads[x][y+1];
	//	for (unsigned int i = 0; i < southQuad.size(); ++i)
	//	{
	//		mNearbyAgents.push_back(southQuad[i]);
	//	}

	//	if (x > 0)
	//	{
	//		std::vector<Agent*> southWQuad = mAgentQuads[x-1][y+1];
	//		for (unsigned int i = 0; i < southWQuad.size(); ++i)
	//		{
	//			mNearbyAgents.push_back(southWQuad[i]);
	//		}
	//	}
	//	if (x < 7)
	//	{
	//		std::vector<Agent*> southEQuad = mAgentQuads[x+1][y+1];
	//		for (unsigned int i = 0; i < southEQuad.size(); ++i)
	//		{
	//			mNearbyAgents.push_back(southEQuad[i]);
	//		}
	//	}
	//}

	//if (x > 0)
	//{
	//	std::vector<Agent*> westQuad = mAgentQuads[x-1][y];
	//	for (unsigned int i = 0; i < westQuad.size(); ++i)
	//	{
	//		mNearbyAgents.push_back(westQuad[i]);
	//	}
	//}

	//if (x < 7)
	//{
	//	std::vector<Agent*> eastQuad = mAgentQuads[x+1][y];
	//	for (unsigned int i = 0; i < eastQuad.size(); ++i)
	//	{
	//		mNearbyAgents.push_back(eastQuad[i]);
	//	}
	//}
	//
	//return mNearbyAgents;
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
