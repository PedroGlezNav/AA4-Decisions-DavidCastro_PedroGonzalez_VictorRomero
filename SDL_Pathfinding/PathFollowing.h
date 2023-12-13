#pragma once
#include "Agent.h"
#include "Vector2D.h"

class PathFollowing :
	public Agent::SteeringBehavior
{
public:
	void applySteeringForce(Agent *agent, float dtime);
};
