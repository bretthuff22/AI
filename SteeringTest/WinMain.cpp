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
	pikachu.SetDestination(SVector2((int)Input_GetMouseScreenX() - pikachuSize/2, (int)Input_GetMouseScreenY() - pikachuSize/2));
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
	if (pikachu.GetSteerMode() == Agent::SteerMode::kPURSUIT)
	{
		destination.Render();
	}
}