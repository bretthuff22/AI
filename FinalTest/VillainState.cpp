#include "VillainState.h"

void IdleState::Enter(Villain& owner)
{

}
void IdleState::Update(Villain& owner)
{
	AIWorld& world = owner.GetWorld();
	std::list<PerceptionData> perceived = owner.GetPerceptionModule().GetMemoryRecords();
	std::list<PerceptionData>::iterator memoryIter = perceived.begin();
	unsigned int agentIndex = 0;
	while (memoryIter != perceived.end())
	{
		PerceptionData& record = (*memoryIter);
		if (record.pAgent->GetAgentType() == Agent::AgentType::kHERO)
		{
			// TODO: CHECK IF HERO IS IN PERCEPTION AREA
			owner.SetDestination(record.pAgent->GetPosition());
			owner.ChangeState(Move);
			break;
		}
		++memoryIter;
		agentIndex++;
	}
}
void IdleState::Exit(Villain& owner)
{

}

void MoveState::Enter(Villain& owner)
{
	owner.SetArrive(true);
	owner.SetSteerMode(Agent::SteerMode::kARRIVE);
}
void MoveState::Update(Villain& owner)
{
	SVector2 destination = owner.GetPosition();

	AIWorld& world = owner.GetWorld();
	std::list<PerceptionData> perceived = owner.GetPerceptionModule().GetMemoryRecords();
	std::list<PerceptionData>::iterator memoryIter = perceived.begin();
	unsigned int agentIndex = 0;
	while (memoryIter != perceived.end())
	{
		PerceptionData& record = (*memoryIter);
		if (record.pAgent->GetAgentType() == Agent::AgentType::kHERO)
		{
			// TODO: CHECK IF HERO IS IN PERCEPTION AREA
			destination = record.pAgent->GetPosition();
			owner.SetDestination(destination);
			break;
		}
		++memoryIter;
		agentIndex++;
	}

	if (Distance(owner.GetPosition(), destination) < 20.0f)
	{
		owner.ChangeState(Idle);
	}
}
void MoveState::Exit(Villain& owner)
{
	owner.SetVelocity(SVector2(0.0f, 0.0f));
	owner.SetArrive(false);
}
