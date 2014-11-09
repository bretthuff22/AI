#include "SteeringModule.h"

#include "Agent.h"
#include "SteeringBehavior.h"

SteeringModule::SteeringModule(Agent* pAgent)
	: mpAgent(pAgent)
{

}

SteeringModule::~SteeringModule()
{
}

void SteeringModule::AddBehavior(SteeringBehavior* behavior)
{
	mBehaviors.push_back(behavior);
}
	
SVector2 SteeringModule::Update(float deltaTime)
{
	SVector2 force;
	const int numBehaviors = mBehaviors.size();
	for (int i = 0; i < numBehaviors; ++i)
	{
		force += mBehaviors[i]->Update(deltaTime) * mBehaviors[i]->GetWeight();
	}

	force.Truncate(mpAgent->GetMaxForce());

	return force;
}