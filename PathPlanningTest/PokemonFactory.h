#ifndef INCLUDED_POKEMON_FACTORY_H
#define INCLUDED_POKEMON_FACTORY_H

#include "Agent.h"
#include "Pikachu.h"

struct PokemonFactory : public AgentFactory
{
	virtual Agent* CreateAgent(AIWorld* world, int typeID)
	{
		Agent* agent = nullptr;
		if (typeID == Agent::AgentType::kPIKACHU)
		{
			agent = new Pikachu(*world);
			agent->Load();

			int screenWidth = IniFile_GetInt("WinWidth", 768.0f);
			int screenHeight = IniFile_GetInt("WinHeight", 768.0f);
			const float x = RandomFloat(100.0f, screenWidth - 100.f);
			const float y = RandomFloat(100.0f, screenHeight - 100.0f);
			const float hx = RandomFloat(100.0f, screenWidth - 100.f);
			const float hy = RandomFloat(100.0f, screenHeight - 100.0f);
			agent->SetPosition(SVector2(x, y));
			agent->SetHeading(SVector2(hx, hy));
			agent->SetSteerMode(Agent::SteerMode::kSEEK);
		}
		return agent;
	}
};

#endif