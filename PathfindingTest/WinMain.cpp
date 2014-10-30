#include <HAIL.h>
#include <SGE.h>
#include "TileMap.h"

using namespace SGE;

const int kWidth = 20;
const int kHeight = 20;
const int kTileSize = 32;
const int kTerrainTiles = 5;
const int kTotalTiles = 7;

TileMap map(kWidth, kHeight);
SGE_Cursor cursor;
SGE_Sprite tiles[kTotalTiles];
Graph graph;
SVector2 start;
SVector2 end;
bool started = false;
bool ended = false;
Node* last;
bool bfs = false;
bool dfs = false;
bool ds = false;
bool as = false;

//const float costMatrix[2][2] = 
//{
//	// Grass	Water
//	{ 1.0f,		2.0f }, 
//	{ 1.5f,		2.0f } 
//};

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
		float dist = Distance(node->position, neighbor->position);
		int x1 = node->position.x/kTileSize;
		int y1 = node->position.y/kTileSize;
		int x2 = neighbor->position.x/kTileSize;
		int y2 = neighbor->position.x/kTileSize;
		// map[y1][x1], map[y2][x2]
		
		dist *= costMatrix[map.GetTile(x1, y1)]*0.5f + costMatrix[map.GetTile(x2, y2)]*0.5f;

		return dist;
	}
};

struct GetH : public ICostFunctor
{
	virtual float operator()(Node* node, Node* neighbor) const 
	{
		float dist = Distance(neighbor->position, end);
		int x1 = neighbor->position.x/kTileSize;
		int y1 = neighbor->position.y/kTileSize;
		int x2 = end.x/kTileSize;
		int y2 = end.x/kTileSize;
		// map[y1][x1], map[y2][x2]
		
		//dist *= costMatrix[map.GetTile(x1, y1)]*0.5f + costMatrix[map.GetTile(x2, y2)]*0.5f;

		return dist;
	}
};

void SGE_Initialize()
{
	cursor.Load("cursor.png");

	tiles[0].Load("block.png");	
	tiles[1].Load("grass.png");
	tiles[2].Load("brick.png");
	tiles[3].Load("sand.png");
	tiles[4].Load("water.png");
	tiles[5].Load("start.png");
	tiles[6].Load("end.png");

	graph.Create(kWidth, kHeight);

	const SVector2 offset(kTileSize * 0.5f, kTileSize * 0.5f);
	for (int y = 0; y < kHeight; ++y)
	{
		for (int x = 0; x < kWidth; ++x)
		{
			Node* node = graph.GetNode(x,y);
			SVector2 position((float)x * kTileSize, (float)y * kTileSize);
			node->position = position + offset;
			if (x != 0 && x != kWidth - 1 && y != 0 && y != kHeight - 1)
			{
				node->walkable = true;
			}
			else
			{
				node->walkable = false;
			}
		}
	}
}

void SGE_Terminate()
{
	cursor.Unload();

	tiles[0].Unload();
	tiles[1].Unload();
	tiles[2].Unload();
	tiles[3].Unload();
	tiles[4].Unload();

	graph.Destroy();
}
	
bool SGE_Update(float deltaTime)
{
	cursor.Update(deltaTime);

	if (Input_IsMousePressed(Mouse::MBUTTON) || Input_IsKeyPressed(Keys::SPACE))
	{
		if (!started)
		{
			start.x = (float)Input_GetMouseScreenX()/kTileSize;
			start.y = (float)Input_GetMouseScreenY()/kTileSize;
			map.SetTile((int)start.x, (int)start.y, kTerrainTiles);
			started = true;
		}
		else if (!ended)
		{
			end.x = (float)Input_GetMouseScreenX()/kTileSize;
			end.y = (float)Input_GetMouseScreenY()/kTileSize;
			map.SetTile((int)end.x, (int)end.y, kTerrainTiles + 1);
			ended = true;
		}
		else if (started && ended)
		{
			started = false;
			ended = false;
			bfs = false;
			dfs = false;
			map.SetTile((int)start.x, (int)start.y, 1);
			map.SetTile((int)end.x, (int)end.y, 1);
		}
	}

	if (Input_IsKeyPressed(Keys::F1) && started && ended)
	{
		if (!bfs)
		{
			BreadthFirstSearch search(graph);
			search.Run((int)start.x, (int)start.y, (int)end.x, (int)end.y);
			if (search.IsFound())
			{
				last = search.GetPath(); 
				bfs = true;
			}
		}
		else
		{
			bfs = false;
		}
	}

	if (Input_IsKeyPressed(Keys::F2) && started && ended)
	{
		if (!dfs)
		{
			DepthFirstSearch search(graph);
			search.Run((int)start.x, (int)start.y, (int)end.x, (int)end.y);
			if (search.IsFound())
			{
				last = search.GetPath(); 
				dfs = true;
			}
		}
		else
		{
			dfs = false;
		}
	}

	if (Input_IsKeyPressed(Keys::F3) && started && ended)
	{
		if (!ds)
		{
			DijkstraSearch search(graph, GetG());
			search.Run((int)start.x, (int)start.y, (int)end.x, (int)end.y);
			if (search.IsFound())
			{
				last = search.GetPath(); 
				ds = true;
			}
		}
		else
		{
			ds = false;
		}
	}

	if (Input_IsKeyPressed(Keys::F4) && started && ended)
	{
		if (!as)
		{
			AStarSearch search(graph, GetG(), GetH());
			search.Run((int)start.x, (int)start.y, (int)end.x, (int)end.y);
			if (search.IsFound())
			{
				last = search.GetPath(); 
				as = true;
			}
		}
		else
		{
			as = false;
		}
	}

	// Change Tile
	if (Input_IsMousePressed(Mouse::LBUTTON))
	{
		int x = Input_GetMouseScreenX()/kTileSize;
		int y = Input_GetMouseScreenY()/kTileSize;
		map.IncrementTile(x, y);
		map.ModTile(x,y,kTerrainTiles);
		unsigned int tileSprite = map.GetTile(x,y);
		if(tileSprite != 0 && tileSprite != 2)
		{
			graph.GetNode(x, y)->walkable = true;
		}
		else
		{
			graph.GetNode(x, y)->walkable = false;
		}
	}

	// Set tile to brick
	if (Input_IsKeyDown(Keys::LCONTROL) && Input_IsMouseDown(Mouse::LBUTTON))
	{
		int x = Input_GetMouseScreenX()/kTileSize;
		int y = Input_GetMouseScreenY()/kTileSize;
		map.SetTile(x, y, 2);
	}

	// Set tile to grass
	if (Input_IsKeyDown(Keys::LCONTROL) && Input_IsMouseDown(Mouse::RBUTTON))
	{
		int x = Input_GetMouseScreenX()/kTileSize;
		int y = Input_GetMouseScreenY()/kTileSize;
		map.SetTile(x, y, 1);
	}

	// Reset map
	if (Input_IsKeyDown(Keys::LCONTROL) && Input_IsKeyDown(Keys::NUMPAD0))
	{
		map.ResetMap();
	}

	// Reset map with no border
	if (Input_IsKeyDown(Keys::LCONTROL) && Input_IsKeyDown(Keys::NUMPAD1))
	{
		map.NoBorder();
	}

	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	for ( int y = 0; y < kHeight; ++y)
	{
		for ( int x = 0; x < kWidth; ++x)
		{
			tiles[map.GetTile(x, y)].SetPosition((float)x*kTileSize, (float)y*kTileSize);
			tiles[map.GetTile(x, y)].Render();

			// Draw neighbor connections
			//Node* node = graph.GetNode(x,y);
			//for (unsigned int n = 0; n < Direction::Count; ++n)
			//{
			//	Node* neighbor = node->neighbors[n];
			//	if (neighbor!= nullptr)
			//	{
			//		Graphics_DebugLine(node->position, neighbor->position, 0xff0000);
			//	}
			//}
		}
	}

	if (bfs || dfs || ds || as)
	{
		Node *node = last;
		while (node->parent != nullptr)
		{
			Graphics_DebugLine(node->position, node->parent->position, 0xff0000);
			node = node->parent;
		}
	}
	cursor.Render();
}