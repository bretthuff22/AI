#include "VillainState.h"

void IdleState::Enter(Villain& owner)
{

}
void IdleState::Update(Villain& owner)
{
	AIWorld& world = owner.GetWorld();
	const std::vector<WorldObject*>& mushrooms = world.GetObjects();
	for (unsigned int i = 0; i < mushrooms.size(); ++i)
	{
		if (mushrooms[i]->IsActive())
		{
			world.SetObjectIndex(i);
			owner.ChangeState(Move);
			break;
		}
	}
}
void IdleState::Exit(Villain& owner)
{

}

void MoveState::Enter(Villain& owner)
{
	AIWorld& world = owner.GetWorld();
	owner.SetDestination(world.GetObjects()[world.GetObjectIndex()]->GetPosition());
	owner.SetArrive(true);
}
void MoveState::Update(Villain& owner)
{
	AIWorld& world = owner.GetWorld();
	SVector2 pos = world.GetObjects()[world.GetObjectIndex()]->GetPosition();
	if (Distance(owner.GetPosition(), pos) < 20.0f)
	{
		owner.ChangeState(Idle);
	}
}
void MoveState::Exit(Villain& owner)
{
	owner.SetVelocity(SVector2(0.0f, 0.0f));
	owner.SetArrive(false);
}
