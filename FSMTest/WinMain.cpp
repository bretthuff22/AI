#include <SGE.h>
using namespace SGE;
#include "Mario.h"
#include "MarioFactory.h"

MarioFactory factory;
AIWorld aiWorld(factory, Agent::AgentType::kMARIO, 0, 1024.0f, 768.0f, 128);
Mario mario(aiWorld);
std::vector<Mushroom*> mushrooms;
unsigned int kNumMushrooms = 5;


void SGE_Initialize()
{
	for (unsigned int i = 0; i < kNumMushrooms; ++i)
	{
		Mushroom* mush = new Mushroom();
		aiWorld.AddObject(mush);
	}
	aiWorld.Load();
	mario.Load();
}

void SGE_Terminate()
{
	mario.Unload();
	aiWorld.Clear();
}

bool SGE_Update(float deltaTime)
{
	mario.Update(deltaTime);

	if (Input_IsKeyPressed(Keys::SPACE))
	{
		const int kWinWidth = IniFile_GetInt("WinWidth", 800);
		const int kWinHeight = IniFile_GetInt("WinHeight", 600);

		const std::vector<WorldObject*>& mushrooms = aiWorld.GetObjects();
		for (int i = 0; i < mushrooms.size(); ++i)
		{
			float x = RandomFloat(0.0f, (float)kWinWidth);
			float y = RandomFloat(0.0f, (float)kWinHeight);
			mushrooms[i]->Spawn(SVector2(x,y));
		}
	}
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	aiWorld.Render();
	mario.Render();
}
