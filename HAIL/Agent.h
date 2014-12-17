#ifndef INCLUDED_AI_AGENT_H
#define INCLUDED_AI_AGENT_H

#include <SGE.h>
using namespace SGE;
#include <list>

class AIWorld;

class Agent
{
public:

	enum SteerMode
	{
		kNONE,
		kSEEK,
		kFLEE,
		kARRIVE,
		kPURSUIT,
		kEVADE,
		kWANDER,
		kINTERPOSE,
		kHIDE,
		kPATHFOLLOWING,
		kOBSTACLEAVOIDANCE,
		kSEPARATION,
		kCOHESION,
		kALIGNMENT,
		kFLOCK
	};

	enum AgentType
	{
		kDEFAULT,
		kPIKACHU,
		kMARIO,
		kHERO,
		kVILLAIN
	};

	Agent(AIWorld& world);
	virtual ~Agent();

	SMatrix33 GetTransform()	const;

	void SetPosition(SVector2 position)					{mPosition = position;}
	void SetDestination(SVector2 destination)			{mDestination = destination;}
	void SetVelocity(SVector2 velocity)					{mVelocity = velocity;}
	void SetHeading(SVector2 heading)					{mHeading = heading;}
	void SetSide(SVector2 side)							{mSide = side;}
	void SetMaxForce(float force)						{mMaxForce = force;}
	void SetMaxSpeed(float speed)						{mMaxSpeed = speed;}
	void SetAgentType(AgentType agentType)				{mAgentType = agentType;}

	AIWorld& GetWorld()			const					{return mWorld;}
	SVector2 GetPosition()		const					{return mPosition;}
	SVector2 GetDestination()	const					{return mDestination;}
	SVector2 GetVelocity()		const					{return mVelocity;}
	SVector2 GetHeading()		const					{return mHeading;}
	SVector2 GetSide()			const					{return mSide;}
	float GetMaxForce()			const					{return mMaxForce;}
	float GetMaxSpeed()			const					{return mMaxSpeed;}
	AgentType GetAgentType()	const					{return mAgentType;}

	virtual void Load() {}
	virtual void SetSteerMode( Agent::SteerMode steerMode) {}
	virtual void AddSteerMode( Agent::SteerMode steerMode) {}
	virtual void Render() {}
	virtual void Update(float deltaTime) {}
	virtual void Unload() {}

	


private:
	AIWorld& mWorld;
	SVector2 mPosition;
	SVector2 mDestination;
	SVector2 mVelocity;

	SVector2 mHeading;
	SVector2 mSide;

	AgentType mAgentType;

	float mMaxForce;
	float mMaxSpeed;

};

typedef std::list<Agent*> AgentList;

#endif //INCLUDED_AI_Agent_H