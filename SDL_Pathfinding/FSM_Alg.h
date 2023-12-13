#pragma once
#include "FSMState.h"

class FSM_Alg : public Agent::Decision_Algorithm
{
private:
	FSMState* currentState = new FSMState_Wander;
public:
	virtual void Update(Agent* agent, float dtime) override;
	void ChangeState(FSMState* newState, Agent* agent);
};