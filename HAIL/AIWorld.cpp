#include "AIWorld.h"

AIWorld::AIWorld(AgentFactory& factory, Agent::AgentType type, unsigned int numAgents, unsigned int screenWidth, unsigned int screenHeight)
	: mFactory(factory)
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
	return newAgent;
}


void AIWorld::Clear()
{
	mObstacles.clear();
	const int kNumAgents = mAgents.size();
	for (int i = 0; i < kNumAgents; ++i)
	{
		mAgents[i]->Unload();
	}

	mAgents.clear();
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
		mAgents[i]->Update(deltaTime);
	}
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
