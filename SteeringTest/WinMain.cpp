#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

#include "Pikachu.h"

SGE_Cursor cursor;
Pikachu pikachu;
float pikachuSize = 128.0f;

void SGE_Initialize()
{
	cursor.Load("carrot.png");	
	pikachu.Load();
}

void SGE_Terminate()
{
	cursor.Unload();
	pikachu.Unload();
}
	
bool SGE_Update(float deltaTime)
{
	cursor.Update(deltaTime);
	pikachu.SetDestination(SVector2((int)Input_GetMouseScreenX() - pikachuSize/2, (int)Input_GetMouseScreenY() - pikachuSize/2));

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
	pikachu.Update(deltaTime);

	// follow the carrot
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	cursor.Render();
	pikachu.Render();
}