#include "Flee.h"

void Flee::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D desired_velocity = agent->getPosition() - agent->getTarget();
	desired_velocity.Normalize();
	desired_velocity *= agent->getMaxVelocity();

	Vector2D steering_force = desired_velocity - agent->getVelocity();
	steering_force /= agent->getMaxVelocity();
	steering_force = steering_force * agent->getMaxForce();

	Vector2D acceleration = steering_force / agent->getMass();
	agent->setVelocity(agent->getVelocity() + acceleration * dtime);
	agent->setVelocity(agent->getVelocity().Truncate(agent->getMaxVelocity()));

	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}