#pragma once
#include "Agent.h"

class Flee :
	public Agent::SteeringBehavior
{
	void applySteeringForce(Agent* agent, float dtime) override;
};