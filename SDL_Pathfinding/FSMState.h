#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include "PathFollowing.h"

class FSMState_Wander;
class FSMState_Chase;
class FSMState_Evade;

class FSMState {
protected:
	float elapsedTime = 1000;

public:
	virtual void Enter(Agent* agent) = 0;
	virtual FSMState* Update(Agent* agent, float dtime) = 0;
};

class FSMState_Wander : public FSMState
{
	virtual void Enter(Agent* agent) override;
	virtual FSMState* Update(Agent* agent, float dtime) override;
};

class FSMState_Chase : public FSMState
{
	virtual void Enter(Agent* agent) override;
	virtual FSMState* Update(Agent* agent, float dtime) override;
};

class FSMState_Evade : public FSMState
{
	virtual void Enter(Agent* agent) override;
	virtual FSMState* Update(Agent* agent, float dtime) override;
};