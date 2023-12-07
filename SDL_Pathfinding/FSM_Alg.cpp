#include "FSM_Alg.h"

void FSM_Alg::Update(Agent* agent, float dtime)
{

}

void FSM_Alg::ChangeState(FSMState* newState, Agent* agent)
{
	currentState = newState;
	currentState->Enter(agent);
}
