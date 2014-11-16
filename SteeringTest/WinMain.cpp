#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

#include "Pikachu.h"

const int kNumObstacles = 3;
AIWorld aiWorld;
SGE_Cursor cursor;
Pikachu pikachu(aiWorld);
float pikachuSize = 128.0f;
SGE_Sprite destination;

SVector2 Wrap(SVector2 vector);

void GenerateAIWorld()
{
	int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
	int screenHeight = IniFile_GetInt("WinHeight", 768.0f);

	aiWorld.Clear();
	for (int i = 0; i < kNumObstacles; ++i)
	{
		const float x = RandomFloat(100.0f, screenWidth - 100.f);
		const float y = RandomFloat(100.0f, screenHeight - 100.0f);
		const float r = RandomFloat(20.0f, 100.0f);
		aiWorld.AddObstacle(SVector2(x, y), r);
	}
}

void SGE_Initialize()
{
	cursor.Load("cursor.png");	
	destination.Load("carrot.png");
	pikachu.Load();

	GenerateAIWorld();
}

void SGE_Terminate()
{
	cursor.Unload();
	destination.Unload();
	pikachu.Unload();
	aiWorld.Clear();
}
	
bool SGE_Update(float deltaTime)
{
	cursor.Update(deltaTime);

	Agent::SteerMode steerMode = pikachu.GetSteerMode();
	if (steerMode != Agent::SteerMode::kWANDER && steerMode != Agent::SteerMode::kINTERPOSE)
	{
		pikachu.SetDestination(SVector2((int)Input_GetMouseScreenX(), (int)Input_GetMouseScreenY()));
	}
	else if (steerMode == Agent::SteerMode::kWANDER)
	{
		SVector2 targetDest = pikachu.GetWanderBehavior().GetTargetDestination();
		destination.SetPosition(targetDest);
	}
	else if (steerMode == Agent::SteerMode::kINTERPOSE)
	{
		AIWorld::Obstacles obstacles = aiWorld.GetObstacles();
		aiWorld.SetObstaclePos(0, Wrap(obstacles[0].center + SVector2(0.0f, 0.5f)));
		aiWorld.SetObstaclePos(1, Wrap(obstacles[1].center + SVector2(0.5f, 0.0f)));

		pikachu.GetInterposeBehavior().SetDestination(obstacles[0].center, obstacles[1].center); 
	}

	if (steerMode == Agent::SteerMode::kPURSUIT)
	{
		SVector2 targetDest = pikachu.GetPursuitBehavior().GetTargetDestination();
		destination.SetPosition(targetDest);
	}

	if (Input_IsKeyPressed(Keys::F1))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kSEEK);
	}
	else if (Input_IsKeyPressed(Keys::F2))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kFLEE);
	}
	else if (Input_IsKeyPressed(Keys::F3))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kARRIVE);
	}
	else if (Input_IsKeyPressed(Keys::F4))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kPURSUIT);
	}
	else if (Input_IsKeyPressed(Keys::F5))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kEVADE);
	}
	else if (Input_IsKeyPressed(Keys::F6))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kWANDER);
	}
	else if (Input_IsKeyPressed(Keys::F7))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kINTERPOSE);
	}
	else if (Input_IsKeyPressed(Keys::F8))
	{
		pikachu.SetSteerMode(Agent::SteerMode::kHIDE);
	}
	
	if (Input_IsKeyPressed(Keys::SPACE))
	{
		GenerateAIWorld();
	}
	if (Input_IsKeyPressed(Keys::PERIOD))
	{
		pikachu.SetMaxSpeed(pikachu.GetMaxSpeed() + 100.0f);
	}

	if (Input_IsKeyPressed(Keys::COMMA))
	{
		pikachu.SetMaxSpeed(Max(pikachu.GetMaxSpeed() - 100.0f, 0.0f));
	}

	pikachu.Update(deltaTime);

	// follow the carrot
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	cursor.Render();
	pikachu.Render();
	if (pikachu.GetSteerMode() == Agent::SteerMode::kPURSUIT || pikachu.GetSteerMode() == Agent::SteerMode::kWANDER)
	{
		destination.Render();
	}

	if (pikachu.GetSteerMode() == Agent::SteerMode::kWANDER)
	{
		SCircle circle = pikachu.GetWanderBehavior().GetCircle();
		Graphics_DebugCircle(circle.center, circle.radius, 0xFF0000);
	}

	aiWorld.Render();
}

SVector2 Wrap(SVector2 vector)
{
	int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
	int screenHeight = IniFile_GetInt("WinHeight", 768.0f);

	while (vector.x > screenWidth)
	{
		vector.x -= screenWidth;
	}

	while (vector.x < 0.0f)
	{
		vector.x += screenWidth;
	}

	while (vector.y > screenHeight)
	{
		vector.y -= screenHeight;
	}

	while (vector.y < 0.0f)
	{
		vector.y += screenHeight;
	}

	return vector;
}