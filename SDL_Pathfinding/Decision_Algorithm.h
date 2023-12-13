#pragma once

class Agent;

class Decision_Algorithm {
public:
	virtual void Update(Agent* agent, float dtime) = 0;
};