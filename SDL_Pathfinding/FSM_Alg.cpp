#include "FSM_Alg.h"

void FSM_Alg::Update(Agent* agent, float dtime)
{
	FSMState* newState = currentState->Update(agent, dtime);
	if (newState != nullptr) ChangeState(newState, agent);
}

void FSM_Alg::ChangeState(FSMState* newState, Agent* agent)
{
	currentState = newState;
	currentState->Enter(agent);
}
