#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

#include "Pikachu.h"

SGE_Cursor cursor;
Pikachu pikachu;
float pikachuSize = 128.0f;
SGE_Sprite destination;

void SGE_Initialize()
{
	cursor.Load("cursor.png");	
	destination.Load("carrot.png");
	pikachu.Load();
}

void SGE_Terminate()
{
	cursor.Unload();
	destination.Unload();
	pikachu.Unload();
}
	
bool SGE_Update(float deltaTime)
{
	cursor.Update(deltaTime);
	if (pikachu.GetSteerMode() != Agent::SteerMode::kWANDER)
	{
		pikachu.SetDestination(SVector2((int)Input_GetMouseScreenX() - pikachuSize/2, (int)Input_GetMouseScreenY() - pikachuSize/2));
	}
	else
	{
		SVector2 targetDest = pikachu.GetWanderBehavior().GetTargetDestination();
		targetDest += SVector2(pikachuSize/2, pikachuSize/2);
		destination.SetPosition(targetDest);
	}

	if (pikachu.GetSteerMode() == Agent::SteerMode::kPURSUIT)
	{
		SVector2 targetDest = pikachu.GetPursuitBehavior().GetTargetDestination();
		targetDest += SVector2(pikachuSize/2, pikachuSize/2);
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
		SVector2 offset = SVector2(pikachuSize*0.5f, pikachuSize*0.5f);
		Graphics_DebugCircle(circle.center + offset, circle.radius, 0xFF0000);
	}
}