#include "SeekBehavior.h"

#include "Agent.h"

SeekBehavior::SeekBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 SeekBehavior::Update(float deltaTime)
{
	SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();
	SVector2 desiredVelocity = Normalize(positionToDestination) * mpAgent->GetMaxSpeed();
	SVector2 force = desiredVelocity - mpAgent->GetVelocity();
	//Graphics_DebugLine(mpAgent->GetPosition(), mpAgent->GetPosition() + desiredVelocity, 0xff0000);
	//Graphics_DebugLine(mpAgent->GetPosition(), mpAgent->GetPosition() + mpAgent->GetVelocity(), 0x0000ff);
	//Graphics_DebugLine(mpAgent->GetPosition(), mpAgent->GetPosition() + force, 0x00ff00);
	return force;
}