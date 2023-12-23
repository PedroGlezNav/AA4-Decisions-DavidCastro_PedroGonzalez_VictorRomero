#include "GOAP_Alg.h"

void GOAP_Alg::CalculatePlan(GOAPWorldState start, GOAPWorldState goal, std::vector<AstarNode*> route)
{
	GOAPWorldState current = goal;
	std::vector<GOAPAction*> path;

	while (current != start) {
		for each (AstarNode* node in route)
		{
			if (*node->actualWs == current) 
			{
				printf_s("%d \n", node->action->effects.value.first);
				path.push_back(node->action);

				current = *node->parentWs;
			}
		}
	}

	std::reverse(path.begin(), path.end());
	plan = path;
}

GOAP_Alg::GOAP_Alg(std::vector<Object*> object, Agent* _agent)
{
	for each (Object * newObject in object)
	{
		GOAPAction* action = new GOAPAction_GoToObject(newObject);
		actions.insert(std::pair<int, GOAPAction*>(newObject->index, action));
	}

	simulatedAgent = new Agent();
	*simulatedAgent = *_agent;
}

void GOAP_Alg::Update(Agent* agent, float dtime)
{
	GOAPWorldState start;
	start.value = std::pair<int, bool>(Colors::BLACK, true);

	GOAPWorldState goal;
	goal.value = std::pair<int, bool>(Colors::GOLD, true);


	if (plan.empty()) AStar(start, goal);
	else {
		if (dynamic_cast<GOAPAction_GoToObject*>(plan[idx_currentAction]) != NULL) {
			if (agent->getPathSize() == 0) {
				std::vector<Vector2D> path = dynamic_cast<GOAPAction_GoToObject*>(plan[idx_currentAction])->GetPath(agent);

				for each (Vector2D point in path)
				{
					agent->addPathPoint(agent->getScene()->getMaze()->cell2pix(point));
				}

				if (idx_currentAction < plan.size() - 1) {
					idx_currentAction++;
				}
			}
		}//if there were other actions, make logic to execute them
	}
}

void GOAP_Alg::AStar(GOAPWorldState start, GOAPWorldState goal)
{
	AstarNode* startNode = new AstarNode();

	startNode->actualWs = &start;

	std::priority_queue<std::pair<float, AstarNode*>, std::vector<std::pair<float, AstarNode*>>, std::greater<std::pair<float, AstarNode*>>> frontier;
	frontier.push(std::make_pair(0.f, startNode));

	AstarNode* nullNode;

	std::vector<AstarNode*> opened;
	opened.push_back(startNode);
	
	while (!frontier.empty()){

		AstarNode* frontierNode = frontier.top().second;
		frontier.pop();

		if (*frontierNode->actualWs == goal) {
			CalculatePlan(start, goal, opened);
			firstIterNoPlan = false;
			return;
		}

		for each (std::pair<int, GOAPAction*> action in actions)
		{
			if (action.second->preconditions == *frontierNode->actualWs) 
			{
				AstarNode* newNode = new AstarNode();
				newNode->parentWs = frontierNode->actualWs;
				newNode->actualWs = &action.second->effects;
				newNode->action = action.second;

				float newCost = 0;
				if (dynamic_cast<GOAPAction_GoToObject*>(action.second) != NULL) {

					for each (Object * obj in *simulatedAgent->getScene()->getKeyPositions()) {
						if (obj->index == action.second->preconditions.value.first) {
							simulatedAgent->setPosition(simulatedAgent->getScene()->getMaze()->cell2pix(obj->position));
						}
					}					
				}//if there were other actions, make agent met preconditions
				
				newCost += action.second->GetCost(simulatedAgent);

				newNode->g = frontierNode->g + newCost;
				newNode->h = frontierNode->h + 1;
				newNode->f = newNode->g + newNode->h;

				opened.push_back(newNode);
				frontier.push(std::pair<float, AstarNode*>(newNode->f, newNode));
			}

		}
		
	}

	firstIterNoPlan = true;
}