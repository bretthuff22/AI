#include "ObstacleAvoidanceBehavior.h"

#include "Agent.h"

#include "AIWorld.h"

ObstacleAvoidanceBehavior::ObstacleAvoidanceBehavior(Agent* pAgent, float weight)
	: SteeringBehavior(pAgent, weight)
{

}

SVector2 ObstacleAvoidanceBehavior::Update(float deltaTime)
{
	// STEP 0: create bounding rectangle using two parallel lines (will draw last two lines in render function)
	float boundingWidth = 70.0f;
	SVector2 offset = Normalize(mpAgent->GetVelocity()) * 0.5f * boundingWidth;
	offset.PerpendicularLH();
	mBoundingLineLeft = SLineSegment(mpAgent->GetPosition() - offset, mpAgent->GetVelocity() + mpAgent->GetPosition() - offset);
	mBoundingLineRight = SLineSegment(mpAgent->GetPosition() + offset, mpAgent->GetVelocity() + mpAgent->GetPosition() + offset);
	SVector2 lateralForce = SVector2(0.0f, 0.0f);
	SVector2 brakingForce = SVector2(0.0f, 0.0f);
	SVector2 pointToAvoidOverall = SVector2(FLT_MAX, 0.0f);

	AIWorld::Obstacles obstacles = mpAgent->GetWorld().GetObstacles();
	unsigned int numObstacles = obstacles.size();
	SVector2 position = mpAgent->GetPosition();
	for (unsigned int i = 0; i < numObstacles; ++i)
	{
		SCircle circle = obstacles[i];
		// STEP 1: eliminate objects that are too far
		float distSqToCircleEdgeFromPos = Length(circle.center - position) - circle.radius; // couldn't use LengthSq because the algebra requires length (l^2 - r^2 != (l - r)^2)
		distSqToCircleEdgeFromPos *= distSqToCircleEdgeFromPos;
		float distSqToBoxEdgeFromPos = LengthSquared(mpAgent->GetVelocity());
		if ( distSqToCircleEdgeFromPos < distSqToBoxEdgeFromPos) 
		{
			// STEP 2: convert to agent space
			SMatrix33 transform = mpAgent->GetTransform();
			transform.Inverse();
			
			position = transform.TransformCoord(position);
			
			circle.center = transform.TransformCoord(circle.center);

			// STEP 3: eliminate objects behind agent
			if (circle.center.x + circle.radius > 0.0f)
			{
				// STEP 4: expand radius by width of bounding box
				float tempRadius = circle.radius + boundingWidth;

				// STEP 5: eliminate obstacles whose y do not overlap with bounding box
				if (abs(circle.center.y) < tempRadius)
				{
					// STEP 6: compute intersection points
					circle.radius = tempRadius;
					SVector2 intersectionPoint1, intersectionPoint2;

					float sqrtStuff = sqrt(circle.radius * circle.radius - circle.center.y * circle.center.y);
					intersectionPoint1.x = -1*sqrtStuff + circle.center.x;
					intersectionPoint1.y = 0.0f;
					intersectionPoint2.x = sqrtStuff + circle.center.x;
					intersectionPoint2.y = 0.0f;
					
					// STEP 7A: Use closest intersection point
					SVector2 pointToAvoid;
					if (intersectionPoint1.x < intersectionPoint2.x)
					{
						pointToAvoid = intersectionPoint1;
					}
					else
					{
						pointToAvoid = intersectionPoint2;
					}

					// STEP 7B: Use closest intersection point including previous loops

					if (pointToAvoid.x < pointToAvoidOverall.x)
					{
						pointToAvoidOverall = pointToAvoid;
				
						// STEP 8: compute lateral force
						lateralForce.y = 10.0f*(Length(mpAgent->GetVelocity()) - pointToAvoid.x);
						if (circle.center.y > 0.0f)
						{
							lateralForce.y*= -1.0f;
						}
						else
						{
							int i = 1;
							i++;
						}

						// STEP 9: compute braking force
						brakingForce.x = 10.0f*(pointToAvoid.x - Length(mpAgent->GetVelocity()));
					}
				}
			}
		}
	}
	
	// STEP 10: convert back to world space

	if (lateralForce != SVector2(0,0) || brakingForce != SVector2(0,0))
	{
		lateralForce = mpAgent->GetTransform().TransformCoord(lateralForce);
		brakingForce = mpAgent->GetTransform().TransformCoord(brakingForce); 
	}


	// SEEK
	SVector2 positionToDestination = mpAgent->GetDestination() - mpAgent->GetPosition();
	positionToDestination = Normalize(positionToDestination);
	SVector2 desiredVelocity = Normalize(positionToDestination + lateralForce + brakingForce) * mpAgent->GetMaxSpeed();
	SVector2 force = desiredVelocity - mpAgent->GetVelocity();
	return force;
}