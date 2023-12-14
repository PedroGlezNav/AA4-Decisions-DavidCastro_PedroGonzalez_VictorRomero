#include "FSMState.h"

void FSMState_Chase::Enter(Agent* agent)
{
    agent->setPathCircleColor(255, 0, 0, 50);
    agent->clearPath();
}

FSMState* FSMState_Chase::Update(Agent* agent, float dtime)
{
    elapsedTime += dtime;

    if (Vector2D::Distance(agent->getScene()->GetAgents()[0]->getPosition(), agent->getPosition()) > agent->getScene()->getMaze()->cell2pix(PLAYER_ENEMY_RADIUS * 3).x) {
        return new FSMState_Wander;
    }
    else if(agent->getScene()->GetAgents()[0]->getHasGun()) {
        return new FSMState_Evade;
    }
    else {
        if (agent->getScene()->getCanEnemiesBehaviour() && elapsedTime >= CHASE_PLAYER_TIME) {
            agent->clearPath();
            elapsedTime = 0;
            std::vector<Vector2D> pathPoints = agent->getNavigationAlgorithm()->CalculatePathNodes(
                agent->getScene()->getMaze()->pix2cell(agent->getPosition()), 
                agent->getScene()->getMaze()->pix2cell(agent->getScene()->GetAgents()[0]->getPosition()),
                agent->getScene()->getGraph(), std::vector<Vector2D>());

            for each (Vector2D point in pathPoints)
            {
                agent->addPathPoint(agent->getScene()->getMaze()->cell2pix(point));
            }
        }
        return nullptr;
    }
}