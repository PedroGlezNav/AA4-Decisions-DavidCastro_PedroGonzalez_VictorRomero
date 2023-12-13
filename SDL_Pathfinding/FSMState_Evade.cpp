#include "FSMState.h"

void FSMState_Evade::Enter(Agent* agent)
{
    agent->setBehavior(new Flee);
}

FSMState* FSMState_Evade::Update(Agent* agent, float dtime)
{
    if (Vector2D::Distance(agent->getScene()->GetAgents()[0]->getPosition(), agent->getPosition()) > PLAYER_ENEMY_RADIUS) {
        return new FSMState_Wander;
    }
    else if (!agent->getScene()->GetAgents()[0]->getHasGun()) {
        return new FSMState_Chase;
    }
    else {
        if (agent->getScene()->getCanEnemiesBehaviour()) {
            std::vector<Vector2D> pathPoints = agent->getNavigationAlgorithm()->CalculatePathNodes(agent->getScene()->getMaze()->pix2cell(agent->getPosition()), agent->getScene()->GetAgents()[0]->getPosition(), agent->getScene()->getGraph(), std::vector<Vector2D>());
            for each (Vector2D point in pathPoints)
            {
                agent->addPathPoint(agent->getScene()->getMaze()->cell2pix(point));
            }
        }
        return nullptr;
    }
}

void FSMState_Evade::Exit()
{
}