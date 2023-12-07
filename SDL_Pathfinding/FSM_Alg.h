#pragma once
#include "FSMState.h"

class FSM_Alg : public Decision_Algorithm
{
private:
	FSMState* currentState;
public:
	virtual void Update(Agent* agent, float dtime) override;
	void ChangeState(FSMState* newState, Agent* agent);
};