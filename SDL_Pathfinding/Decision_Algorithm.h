#pragma once
#include "Agent.h"

class Decision_Algorithm {
public:
	virtual void Update(Agent* agent, float dtime) = 0;
};