#include "HideBehavior.h"

#include "Agent.h"

#include "AIWorld.h"

HideBehavior::HideBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 HideBehavior::Update(float deltaTime)
{
	SVector2 pos = mpAgent->GetPosition();
	SVector2 hideDestination = pos;
	SVector2 hunterDestination = mpAgent->GetDestination();
	float curDistSq = FLT_MAX;
	

	AIWorld::Obstacles obstacles = mpAgent->GetWorld().GetObstacles();

	const int kNumObstacles = obstacles.size();
	for (int i = 0; i < kNumObstacles; ++i)
	{
		SCircle& obstacle = obstacles[i];
		SVector2 hideSpot = (obstacle.center - Normalize(hunterDestination - obstacle.center)*(obstacle.radius + 50.0f)); // * 1.1f fix this 1.1f
		if (LengthSquared(hunterDestination - obstacle.center) > LengthSquared(hunterDestination - hideSpot))
		{
			hideSpot = (obstacle.center + Normalize(hunterDestination - obstacle.center)*(obstacle.radius + 50.0f)); // * 1.1f fix this 1.1f
		}

		float distSq = LengthSquared(hideSpot - pos);

		if (distSq < curDistSq)
		{
			hideDestination = hideSpot;
			curDistSq = distSq;
		}
	}


	// Arrive
	SVector2 positionToDestination = hideDestination - mpAgent->GetPosition();
	SVector2 posToDestNorm = Normalize(positionToDestination);

	float maxSpeed = mpAgent->GetMaxSpeed();

	SVector2 desiredVelocity = posToDestNorm * maxSpeed;

	float distSq = LengthSquared(positionToDestination);
	float velocitySq = LengthSquared(mpAgent->GetVelocity());
	float slowingRadiusSq = 160000.0f;
	float stopRadiusSq = 25.0f;

	if (distSq < velocitySq)
	{
		if (distSq < slowingRadiusSq && distSq > stopRadiusSq )
		{
			//desiredVelocity = -velocitySq/(2*sqrt(distSq));
			desiredVelocity = posToDestNorm * maxSpeed * distSq/(slowingRadiusSq*slowingRadiusSq*slowingRadiusSq*slowingRadiusSq);// * maxSpeed/(distSq*distSq);
		}
		else if (distSq <= stopRadiusSq)
		{
			mpAgent->SetPosition(hideDestination);
			desiredVelocity = SVector2(0.0f, 0.0f);
		}
	}

	return desiredVelocity - mpAgent->GetVelocity();
}