#include "MarioStates.h"

void IdleState::Enter(Mario& owner)
{

}
void IdleState::Update(Mario& owner)
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
void IdleState::Exit(Mario& owner)
{

}

void MoveState::Enter(Mario& owner)
{
	AIWorld& world = owner.GetWorld();
	owner.SetDestination(world.GetObjects()[world.GetObjectIndex()]->GetPosition());
	owner.SetArrive(true);
}
void MoveState::Update(Mario& owner)
{
	AIWorld& world = owner.GetWorld();
	SVector2 pos = world.GetObjects()[world.GetObjectIndex()]->GetPosition();
	if (Distance(owner.GetPosition(), pos) < 20.0f)
	{
		owner.ChangeState(Eat);
	}
}
void MoveState::Exit(Mario& owner)
{
	owner.SetVelocity(SVector2(0.0f, 0.0f));
	owner.SetArrive(false);
}

void EatState::Enter(Mario& owner)
{

}
void EatState::Update(Mario& owner)
{
	AIWorld& world = owner.GetWorld();
	Mushroom* mushroom = (Mushroom*)world.GetObjects()[world.GetObjectIndex()];
	mushroom->Eat();
	owner.ChangeState(Idle);
}
void EatState::Exit(Mario& owner)
{

}