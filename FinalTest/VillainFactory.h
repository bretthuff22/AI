#ifndef INCLUDED_VILLAIN_FACTORY_H
#define INCLUDED_VILLAIN_FACTORY_H

#include "Agent.h"
#include "HAIL.h"
#include "Hero.h"
//#include "Villain.h"

struct VillainFactory : public AgentFactory
{
	virtual Agent* CreateAgent(AIWorld* world, int typeID)
	{
		Agent* agent = nullptr;
		if (typeID == Agent::AgentType::kPIKACHU)
		{
			agent = new Hero(*world); // TODO: CHANGE TO VILLAIN
			agent->Load();

			int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
			int screenHeight = IniFile_GetInt("WinHeight", 768.0f);
			float x = -1.0f;
			float y = -1.0f;
			float hx = -1.0f;
			float hy = -1.0f;

			while ( (y < 0 || y > screenHeight - 1 || x < 0 || x < screenWidth - 1) ||
				 ( ( y > (int)screenHeight*0.2f && y < (int)screenHeight*0.8f	 ) && (  x > (int)screenWidth*0.2f && x < (int)screenWidth*0.8f ) ) )
			{
				x = RandomFloat(100.0f, screenWidth - 100.f);
				y = RandomFloat(100.0f, screenHeight - 100.0f);
				hx = RandomFloat(100.0f, screenWidth - 100.f);
				hy = RandomFloat(100.0f, screenHeight - 100.0f);
			}
			agent->SetPosition(SVector2(x, y));
			agent->SetHeading(SVector2(hx, hy));
			agent->SetSteerMode(Agent::SteerMode::kARRIVE);
		}
		return agent;
	}
};

#endif