#include "MarioStates.h"

void IdleState::Enter(Mario& owner)
{

}
void IdleState::Update(Mario& owner)
{
	std::vector<Mushroom>& mushrooms = owner.GetMushrooms();
	for (int i = 0; i < mushrooms.size(); ++i)
	{
		if (mushrooms[i].IsActive())
		{
			owner.GetMushroomIndex() = i;
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
	Mushroom& mushroom = owner.GetMushrooms()[owner.GetMushroomIndex()];
	owner.SetDestination(mushroom.GetPosition());
	owner.SetArrive(true);
}
void MoveState::Update(Mario& owner)
{
	Mushroom& mushroom = owner.GetMushrooms()[owner.GetMushroomIndex()];
	if (Distance(owner.GetPosition(), mushroom.GetPosition()) < 20.0f)
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
	Mushroom& mushroom = owner.GetMushrooms()[owner.GetMushroomIndex()];
	mushroom.Eat();
	owner.ChangeState(Idle);
}
void EatState::Exit(Mario& owner)
{

}