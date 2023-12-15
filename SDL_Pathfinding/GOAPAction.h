#pragma once
#include "Agent.h"

class GOAPWorldState {
public:
	std::vector<bool> values;
	std::vector<bool> mask;
};

class GOAPAction {
public:
	GOAPWorldState preconditions;
	GOAPWorldState effects;
	int cost;
	virtual void Update(Agent* agent, float dtime) = 0;
};