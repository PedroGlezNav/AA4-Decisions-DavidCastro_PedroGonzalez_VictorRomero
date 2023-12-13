#pragma once
#include "Agent.h"

class Seek :
	public Agent::SteeringBehavior
{
public:
	void applySteeringForce(Agent *agent, float dtime);
};
