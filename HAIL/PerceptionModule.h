#ifndef INCLUDED_AI_PERCEPTIONMODULE_H
#define INCLUDED_AI_PERCEPTIONMODULE_H

#include <SGE.h>
using namespace SGE;

#include "Agent.h"
#include <list>

enum PerceptionLevel
{
	Unknown,
	Suspect,
	Confirm
};

struct PerceptionData
{
	const Agent* pAgent;

	PerceptionLevel level;
	SVector2 lastSeenLocation;
	float lastRecordedTime;
	float importance;

	PerceptionData()
		: pAgent(nullptr)
		, level(Unknown)
		, lastSeenLocation(0.0f, 0.0f)
		, lastRecordedTime(FLT_MAX)
		, importance(0.0f)
	{

	}
};

typedef std::list<PerceptionData> MemoryRecords;

class PerceptionModule
{
public:
	PerceptionModule(Agent& owner);

	void Update(float deltaTime);

	const MemoryRecords& GetMemoryRecords() const; 

	float GetViewDistance() const { return mViewDistance; }
	float GetViewAngle()	const { return mViewAngle; } 
	float GetMemorySpan()	const { return mMemorySpan; }

	void SetViewDistance(float distance)	{ mViewDistance = distance; }
	void SetViewAngle(float angle)			{ mViewAngle = angle; } 
	void SetMemorySpan(float span)			{ mMemorySpan = span; }

private:
	void AgeMemoryRecords(float deltaTime);
	void UpdatePerception();
	void UpdateImportance();
	void CalculateImportance(PerceptionData& record);

	MemoryRecords mMemoryRecords;

	Agent& mOwner;

	float mViewDistance;
	float mViewAngle; 
	float mMemorySpan;
};

#endif