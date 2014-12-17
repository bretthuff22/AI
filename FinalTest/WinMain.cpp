#include <HAIL.h>
#include <SGE.h>
#include "TileMap.h"
#include "VillainFactory.h"
#include "Hero.h"

using namespace SGE;

const int kWidth = 40;
const int kHeight = 30;
const int kTileSize = 32;
const int kTerrainTiles = 5;

const float viewRadius = 250.0f;

TileMap map(kWidth, kHeight);
SGE_Sprite tiles[kTerrainTiles];
Graph graph;
float villainSize = 90.0f; // FIX
unsigned int kNumVillains = 6;
VillainFactory factory;
AIWorld aiWorld(factory, Agent::AgentType::kVILLAIN, kNumVillains, 768.0f, 768.0f, (int)villainSize);
Hero hero(aiWorld);

void GenerateAIWorld()
{
	int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
	int screenHeight = IniFile_GetInt("WinHeight", 768.0f);

	aiWorld.Clear();
	aiWorld.SetScreenSize(screenWidth, screenHeight);

	SVector2 nw(416, 320);
	SVector2 ne(896, 320);
	SVector2 sw(416, 672);
	SVector2 se(896, 672);

	aiWorld.AddWall(nw, ne);
	aiWorld.AddWall(nw, sw);
	aiWorld.AddWall(sw, se);
	aiWorld.AddWall(ne, se);

	for (int i = 0; i < kNumVillains; ++i)
	{
		Agent* newAgent = aiWorld.CreateAgent(Agent::AgentType::kVILLAIN);
	}
}

const float costMatrix[7] = 
{
	FLT_MAX,
	1.0f,
	FLT_MAX,
	2.0f,
	4.0f,
	1.0f,
	1.0f
};

struct GetG : public ICostFunctor
{
	virtual float operator()(Node* node, Node* neighbor) const 
	{
		float dist = Distance(node->position/kTileSize, neighbor->position/kTileSize);
		int x1 = (int)node->position.x/kTileSize;
		int y1 = (int)node->position.y/kTileSize;
		int x2 = (int)neighbor->position.x/kTileSize;
		int y2 = (int)neighbor->position.x/kTileSize;

		if (map.GetTile(x1, y1) != 0 && map.GetTile(x2, y2) != 0 && map.GetTile(x1, y1) != 2  && map.GetTile(x2, y2) != 2 )
		{
			dist *= costMatrix[map.GetTile(x1, y1)]*0.5f + costMatrix[map.GetTile(x2, y2)]*0.5f;
		}
		

		return dist;
	}
};

struct GetH : public ICostFunctor
{
	virtual float operator()(Node* neighbor, Node* endNode) const 
	{
		float dist = Distance(neighbor->position, endNode->position);

		return dist;
	}
};

void SGE_Initialize()
{
	tiles[0].Load("block.png");	
	tiles[1].Load("grass.png");
	tiles[2].Load("brick.png");
	tiles[3].Load("sand.png");
	tiles[4].Load("water.png");

	graph.Create(kWidth, kHeight);

	const SVector2 offset(kTileSize * 0.5f, kTileSize * 0.5f);
	for (int y = 0; y < kHeight; ++y)
	{
		for (int x = 0; x < kWidth; ++x)
		{
			Node* node = graph.GetNode(x,y);
			SVector2 position((float)x * kTileSize, (float)y * kTileSize);
			node->position = position + offset;
			unsigned int nodeType = map.GetTile(x, y);
			if (nodeType == 0 || nodeType == 2)
			{
				node->walkable = false;
			}
			else
			{
				node->walkable = true;
			}

			//if (x != 0 && x != kWidth - 1 && y != 0 && y != kHeight - 1)
			//{
			//	node->walkable = true;
			//}
			//else
			//{
			//	node->walkable = false;
			//}
		}
	}

	hero.Load();
	hero.SetPosition(SVector2(100.0f, 100.0f));
	GenerateAIWorld();
	aiWorld.AddAgent(hero);
}

void SGE_Terminate()
{
	tiles[0].Unload();
	tiles[1].Unload();
	tiles[2].Unload();
	tiles[3].Unload();
	tiles[4].Unload();

	hero.Unload();
	graph.Destroy();
}
	
bool SGE_Update(float deltaTime)
{
	hero.Update(deltaTime);
	aiWorld.Update(deltaTime);
	SVector2 heroPosition = hero.GetPosition();
	Node* curHeroNode = graph.GetNode((int)heroPosition.x/kTileSize, (int)heroPosition.y/kTileSize);
	if (Input_IsKeyPressed(Keys::UP) && curHeroNode->neighbors[Direction::North]->neighbors[Direction::North]->walkable)
	{
		heroPosition.y -= kTileSize;
		hero.SetPosition(heroPosition);
	}
	else if (Input_IsKeyPressed(Keys::DOWN) && curHeroNode->neighbors[Direction::South]->neighbors[Direction::South]->walkable)
	{
		heroPosition.y += kTileSize;
		hero.SetPosition(heroPosition);
	}
	else if (Input_IsKeyPressed(Keys::LEFT) && curHeroNode->neighbors[Direction::West]->neighbors[Direction::West]->walkable)
	{
		heroPosition.x -= kTileSize;
		hero.SetPosition(heroPosition);
	}
	else if (Input_IsKeyPressed(Keys::RIGHT) && curHeroNode->neighbors[Direction::East]->walkable)
	{
		heroPosition.x += kTileSize;
		hero.SetPosition(heroPosition);
	}
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	//for ( int y = 0; y < kHeight; ++y)
	//{
	//	for ( int x = 0; x < kWidth; ++x)
	//	{
	//		tiles[map.GetTile(x, y)].SetPosition((float)x*kTileSize, (float)y*kTileSize);
	//		tiles[map.GetTile(x, y)].Render();
	//	}
	//}
	SVector2 heroPosition = hero.GetPosition();

	for ( int y = 0; y < kHeight; ++y)
	{
		for ( int x = 0; x < kWidth; ++x)
		{
			SVector2 pos(x*kTileSize, y*kTileSize);
			if (DistanceSquared(pos, heroPosition) < viewRadius*viewRadius)
			{
				tiles[map.GetTile(x, y)].SetPosition((float)x*kTileSize, (float)y*kTileSize);
				tiles[map.GetTile(x, y)].Render();
			}
		}
	}

	const std::vector<Agent*> agents = aiWorld.GetAgents();

	const int size = agents.size();

	for (int i = 0; i < size; ++i)
	{
		SVector2 villainPos = agents[i]->GetPosition();
		if (DistanceSquared(villainPos, heroPosition) < viewRadius*viewRadius)
		{
			agents[i]->Render();
		}
	}
	//hero.Render();
}