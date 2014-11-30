#include <SGE.h>
using namespace SGE;
#include "Mario.h"
#include "MarioFactory.h"

MarioFactory factory;
AIWorld aiWorld(factory, Agent::AgentType::kMARIO, 0, 1024.0f, 768.0f);
Mario mario(aiWorld);


void SGE_Initialize()
{
	mario.Load();
}

void SGE_Terminate()
{
	mario.Unload();
}

bool SGE_Update(float deltaTime)
{
	mario.Update(deltaTime);

	if (Input_IsKeyPressed(Keys::SPACE))
	{
		const int kWinWidth = IniFile_GetInt("WinWidth", 800);
		const int kWinHeight = IniFile_GetInt("WinHeight", 600);

		std::vector<Mushroom>& mushrooms = mario.GetMushrooms();
		for (int i = 0; i < mushrooms.size(); ++i)
		{
			float x = RandomFloat(0.0f, (float)kWinWidth);
			float y = RandomFloat(0.0f, (float)kWinHeight);
			mushrooms[i].Spawn(SVector2(x,y));
		}
	}
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	mario.Render();
}
