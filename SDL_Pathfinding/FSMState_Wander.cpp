#include "FSMState.h"

void FSMState_Wander::Enter(Agent* agent)
{
    agent->setBehavior(new PathFollowing);
}

FSMState* FSMState_Wander::Update(Agent* agent, float dtime)
{
    if (Vector2D::Distance(agent->getScene()->GetAgents()[0]->getPosition(), agent->getPosition()) < PLAYER_ENEMY_RADIUS) {
        return new FSMState_Chase;
    }
    else {
		if (agent->getPathSize() == 0 && agent->getScene()->getCanEnemiesBehaviour()) {
			Vector2D rand_cell = Vector2D(-1, -1);
			while (!agent->getScene()->getMaze()->isValidCell(rand_cell)) {
				rand_cell = Vector2D((float)(rand() % agent->getScene()->getMaze()->getNumCellX()), (float)(rand() % agent->getScene()->getMaze()->getNumCellY()));
			}
			std::vector<Vector2D> pathPoints = agent->getNavigationAlgorithm()->CalculatePathNodes(agent->getScene()->getMaze()->pix2cell(agent->getPosition()), rand_cell, agent->getScene()->getGraph(), std::vector<Vector2D>());
			for each (Vector2D point in pathPoints)
			{
				agent->addPathPoint(agent->getScene()->getMaze()->cell2pix(point));
			}
		}
        return nullptr;
    }
}

void FSMState_Wander::Exit()
{
}