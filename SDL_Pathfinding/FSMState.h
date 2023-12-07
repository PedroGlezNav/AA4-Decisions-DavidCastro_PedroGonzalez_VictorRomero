#pragma once
#include "Decision_Algorithm.h"

class FSMState {
public:
	virtual void Enter(Agent* agent) = 0;
	virtual FSMState* Update(Agent* agent, float dtime) = 0;
	virtual void Exit() = 0;
};