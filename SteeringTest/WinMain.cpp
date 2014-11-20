#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

#include "Pikachu.h"

const int kNumObstacles = 3;
AIWorld aiWorld;
SGE_Cursor cursor;
Pikachu pikachu(aiWorld);
unsigned int kNumPikachus = 30;
//Pikachu& pikachus = new Pikachu(aiWorld)[kNumPikachus];
Pikachu** pikachus = new Pikachu*[kNumPikachus];
float pikachuSize = 128.0f;
SGE_Sprite destination;
SGE_Sprite destinations[10];
unsigned int destCounter = 0;
SGE_Font behaviorFonts[13];

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

void LoadPikachus()
{
	int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
	int screenHeight = IniFile_GetInt("WinHeight", 768.0f);

	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i] = new Pikachu(aiWorld);
		pikachus[i]->Load();

		const float x = RandomFloat(100.0f, screenWidth - 100.f);
		const float y = RandomFloat(100.0f, screenHeight - 100.0f);
		//const float dx = RandomFloat(100.0f, screenWidth - 100.f);
		//const float dy = RandomFloat(100.0f, screenHeight - 100.0f);
		const float hx = RandomFloat(100.0f, screenWidth - 100.f);
		const float hy = RandomFloat(100.0f, screenHeight - 100.0f);
		pikachus[i]->SetPosition(SVector2(x, y));
		//pikachus[i]->SetDestination(SVector2(dx, dy));
		pikachus[i]->SetHeading(SVector2(hx, hy));
		pikachus[i]->SetSteerMode(Agent::SteerMode::kSEEK);
	}

	for (int i = 0; i < kNumPikachus; ++i)
	{
		for (int j = 0; j < kNumPikachus; ++j)
		{
			pikachus[i]->AddAgent(*pikachus[j]); 
		}
	}
}

void RenderPikachus()
{
	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i]->Render();
	}
}

void SetSteerModePikachus(Agent::SteerMode mode)
{
	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i]->SetSteerMode(mode);
	}
}

void UpdatePikachus(float deltaTime)
{
	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i]->Update(deltaTime);
	}
}

void SetDestinationPikachus(SVector2 dest)
{
	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i]->SetDestination(dest);
	}
}

void SetMaxSpeedPikachus(float speed)
{
	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i]->SetMaxSpeed(speed);
	}
}

void TerminatePikachus()
{
	for (int i = 0; i < kNumPikachus; ++i)
	{
		pikachus[i]->Unload();
	}

	delete[] pikachus;
}

void SGE_Initialize()
{
	cursor.Load("cursor.png");	
	destination.Load("carrot.png");
	pikachu.Load();

	for (unsigned int i = 0; i < 10; ++i)
	{
		destinations[i].Load("bullet2.png");
		destinations[i].SetPosition(-1.0f, -1.0f);
	}

	GenerateAIWorld();

	for (unsigned int i = 0; i < 13; ++i)
	{
		behaviorFonts[i].Load(12, false, false);
		behaviorFonts[i].SetColor(0,0,255);
	}

	behaviorFonts[0].SetColor(255,0,0);

	LoadPikachus();
}

void SGE_Terminate()
{
	cursor.Unload();
	destination.Unload();
	pikachu.Unload();
	aiWorld.Clear();
	for (unsigned int i = 0; i < 10; ++i)
	{
		behaviorFonts[i].Unload();
	}

	TerminatePikachus();
}
	
bool SGE_Update(float deltaTime)
{
	cursor.Update(deltaTime);

	Agent::SteerMode steerMode = pikachu.GetSteerMode();
	if (steerMode != Agent::SteerMode::kWANDER && steerMode != Agent::SteerMode::kINTERPOSE && steerMode != Agent::SteerMode::kPATHFOLLOWING)
	{
		pikachu.SetDestination(SVector2((int)Input_GetMouseScreenX(), (int)Input_GetMouseScreenY()));
		SetDestinationPikachus(SVector2((int)Input_GetMouseScreenX(), (int)Input_GetMouseScreenY()));
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

	if (steerMode == Agent::SteerMode::kPATHFOLLOWING)
	{
		if ( Input_IsMousePressed(0) && destCounter < 10)
		{
			SVector2 targetDest = SVector2(SVector2((int)Input_GetMouseScreenX(), (int)Input_GetMouseScreenY()));
			pikachu.AddDestinationForPathFollowing(targetDest);
			destinations[destCounter].SetPosition(targetDest);
			destCounter++;
		}
	}
	else
	{
		 destCounter = 0;
	}

	if (steerMode == Agent::SteerMode::kSEPARATION || steerMode == Agent::SteerMode::kCOHESION || steerMode == Agent::SteerMode::kALIGNMENT)
	{
		UpdatePikachus(deltaTime);
	}

	if (Input_IsKeyPressed(Keys::F1) && !Input_IsKeyDown(Keys::LSHIFT))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kSEEK);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F2) && !Input_IsKeyDown(Keys::LSHIFT))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kFLEE);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F3) && !Input_IsKeyDown(Keys::LSHIFT))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kARRIVE);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F4))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kPURSUIT);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F5))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kEVADE);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F6))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kWANDER);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F7))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kINTERPOSE);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F8))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kHIDE);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F9))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kPATHFOLLOWING);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);

		SVector2 targetDest = pikachu.GetDestination();
		pikachu.AddDestinationForPathFollowing(targetDest);
		destinations[destCounter].SetPosition(targetDest);
		destCounter++;
	}
	else if (Input_IsKeyPressed(Keys::F10))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kOBSTACLEAVOIDANCE);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F1) && Input_IsKeyDown(Keys::LSHIFT))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kSEPARATION);
		SetSteerModePikachus(Agent::SteerMode::kSEPARATION);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F2) && Input_IsKeyDown(Keys::LSHIFT))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kCOHESION);
		SetSteerModePikachus(Agent::SteerMode::kCOHESION);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}
	else if (Input_IsKeyPressed(Keys::F3) && Input_IsKeyDown(Keys::LSHIFT))
	{
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(0,0,255);
		pikachu.SetSteerMode(Agent::SteerMode::kALIGNMENT);
		SetSteerModePikachus(Agent::SteerMode::kALIGNMENT);
		behaviorFonts[pikachu.GetSteerMode() - Agent::SteerMode::kSEEK].SetColor(255,0,0);
	}


	if (Input_IsKeyPressed(Keys::SPACE))
	{
		GenerateAIWorld();
	}
	if (Input_IsKeyPressed(Keys::PERIOD))
	{
		float speed = pikachu.GetMaxSpeed() + 100.0f;
		pikachu.SetMaxSpeed(speed);
		SetMaxSpeedPikachus(speed);
	}

	if (Input_IsKeyPressed(Keys::COMMA))
	{
		float speed = Max(pikachu.GetMaxSpeed() - 100.0f, 0.0f);
		pikachu.SetMaxSpeed(speed);
		SetMaxSpeedPikachus(speed);
	}

	pikachu.Update(deltaTime);

	// follow the carrot
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
	int screenHeight = IniFile_GetInt("WinHeight", 768.0f);

	behaviorFonts[0].Print("F1  - SEEK",				screenWidth - 200.0f,	10.0f);
	behaviorFonts[1].Print("F2  - FLEE",				screenWidth - 200.0f,	30.0f);
	behaviorFonts[2].Print("F3  - ARRIVE",				screenWidth - 200.0f,	50.0f);
	behaviorFonts[3].Print("F4  - PURSUIT",				screenWidth - 200.0f,	70.0f);
	behaviorFonts[4].Print("F5  - EVADE",				screenWidth - 200.0f,	90.0f);
	behaviorFonts[5].Print("F6  - WANDER",				screenWidth - 200.0f,	110.0f);
	behaviorFonts[6].Print("F7  - INTERPOSE",			screenWidth - 200.0f,	130.0f);
	behaviorFonts[7].Print("F8  - HIDE",				screenWidth - 200.0f,	150.0f);
	behaviorFonts[8].Print("F9  - PATH FOLLOWING",		screenWidth - 200.0f,	170.0f);
	behaviorFonts[9].Print("F10 - OBSTACLE AVOIDANCE",	screenWidth - 200.0f,	190.0f);

	behaviorFonts[10].Print("SHIFT + F1 - SEPARATION",	screenWidth - 200.0f,	250.0f);
	behaviorFonts[11].Print("SHIFT + F2 - COHESION",	screenWidth - 200.0f,	270.0f);
	behaviorFonts[12].Print("SHIFT + F3 - ALIGN",		screenWidth - 200.0f,	290.0f);
	
	Agent::SteerMode steerMode = pikachu.GetSteerMode();
	cursor.Render();

	for (unsigned int i = 0; i < destCounter; ++i)
	{
		destinations[i].Render();
	}

	if (steerMode != Agent::SteerMode::kSEPARATION && steerMode != Agent::SteerMode::kCOHESION && steerMode != Agent::SteerMode::kALIGNMENT)
	{
		pikachu.Render();
	}
	else
	{
		RenderPikachus();
	}

	if (steerMode == Agent::SteerMode::kPURSUIT || steerMode == Agent::SteerMode::kWANDER)
	{
		destination.Render();
	}

	if (steerMode == Agent::SteerMode::kWANDER)
	{
		SCircle circle = pikachu.GetWanderBehavior().GetCircle();
		Graphics_DebugCircle(circle.center, circle.radius, 0xFF0000);
	}

	aiWorld.Render();

	if (steerMode == Agent::SteerMode::kOBSTACLEAVOIDANCE)
	{
		Graphics_DebugLine(pikachu.GetObstacleAvoidanceBehavior().GetBoundingLineLeft(), 0x00ff00);
		Graphics_DebugLine(pikachu.GetObstacleAvoidanceBehavior().GetBoundingLineRight(), 0x00ff00);
		Graphics_DebugLine(pikachu.GetObstacleAvoidanceBehavior().GetBoundingLineLeft().from, pikachu.GetObstacleAvoidanceBehavior().GetBoundingLineRight().from, 0x00ff00);
		Graphics_DebugLine(pikachu.GetObstacleAvoidanceBehavior().GetBoundingLineLeft().to, pikachu.GetObstacleAvoidanceBehavior().GetBoundingLineRight().to, 0x00ff00);
	}
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