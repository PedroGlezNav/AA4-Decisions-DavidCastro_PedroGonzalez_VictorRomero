#include "FSMState.h"

void FSMState_Evade::Enter(Agent* agent)
{
    agent->setPathCircleColor(0, 255, 0, 50);
    agent->clearPath();
}

FSMState* FSMState_Evade::Update(Agent* agent, float dtime)
{
    elapsedTime += dtime;

    if (Vector2D::Distance(agent->getScene()->GetAgents()[0]->getPosition(), agent->getPosition()) > agent->getScene()->getMaze()->cell2pix(PLAYER_ENEMY_RADIUS * 3).x) {
        return new FSMState_Wander;
    }
    else if (!agent->getScene()->GetAgents()[0]->getHasGun()) {
        return new FSMState_Chase;
    }
    else {
        if (agent->getScene()->getCanEnemiesBehaviour() && elapsedTime >= EVADE_PLAYER_TIME) {
            elapsedTime = 0;
            agent->clearPath();

            Vector2D cell = agent->getScene()->getMaze()->pix2cell(agent->getPosition() * 3 - agent->getScene()->GetAgents()[0]->getPosition());

            if (!agent->getScene()->getMaze()->isValidCell(cell)) {
                Vector2D direction = agent->getScene()->GetAgents()[0]->getPosition() - agent->getPosition();
                Vector2D pp1 = (agent->getPosition() + Vector2D(-direction.y, direction.x)) * 10000;
                Vector2D pp2 = (agent->getPosition() + Vector2D(direction.y, -direction.x)) * 10000;

                while (!agent->getScene()->getMaze()->isValidCell(cell) /* && !agent->intersect(agent->getPosition(), cell, pp1, pp2)*/ &&
                    Vector2D::Distance(agent->getScene()->getMaze()->pix2cell(agent->getScene()->GetAgents()[0]->getPosition()), cell) > PLAYER_RANDOM_EVADE_LIMIT) {
                    cell = Vector2D((float)(rand() % agent->getScene()->getMaze()->getNumCellX()), (float)(rand() % agent->getScene()->getMaze()->getNumCellY()));
                }
            }

            std::vector<Vector2D> pathPoints = agent->getNavigationAlgorithm()->CalculatePathNodes(agent->getScene()->getMaze()->pix2cell(agent->getPosition()), cell, agent->getScene()->getGraph(), std::vector<Vector2D>());
            for each (Vector2D point in pathPoints)
            {
                agent->addPathPoint(agent->getScene()->getMaze()->cell2pix(point));
            }

        }
        return nullptr;
    }
}