#include "Agent.h"

Agent::Agent(AIWorld& world)
	: mWorld(world)
	, mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mHeading(1.0f, 0.0f)
	, mSide(0.0f, 1.0f)
	, mMaxForce(0.0f)
	, mMaxSpeed(0.0f)
{

}

Agent::~Agent()
{

}

SMatrix33 Agent::GetTransform() const
{
	SMatrix33 transform;
	transform._11 = mHeading.x;
	transform._12 = mHeading.y;
	transform._21 = mSide.x;
	transform._22 = mSide.y;
	transform._31 = mPosition.x;
	transform._32 = mPosition.y;

	return transform;
}
//
//void Agent::AddAgent(Agent& agent)					
//{ 
//	mWorldAgents.push_back(&agent);
//}