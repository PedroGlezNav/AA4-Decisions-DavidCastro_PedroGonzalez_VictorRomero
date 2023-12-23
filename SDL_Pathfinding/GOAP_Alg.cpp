#include "GOAP_Alg.h"

void GOAP_Alg::CalculatePlan(GOAPWorldState start, GOAPWorldState goal, std::vector<std::pair<AstarNode*, AstarNode*>> cameFrom)
{
	GOAPWorldState current = goal;
	std::vector<GOAPAction*> path;

	while (current != start) {
		for each (std::pair<AstarNode*, AstarNode*> connection in cameFrom)
		{
			if (connection.second->actualWs == current) {
				path.push_back(connection.second->action);

				current = connection.second->parentWs;

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

	simulatedAgent = _agent;
}

void GOAP_Alg::Update(Agent* agent, float dtime)
{
	if (!firstIterNoPlan) {
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
						agent->addPathPoint(point);
					}

					idx_currentAction++;

				}
			}//if there were other actions, make logic to execute them
		}
	}
}

void GOAP_Alg::AStar(GOAPWorldState start, GOAPWorldState goal)
{
	AstarNode* startNode = new AstarNode();

	startNode->parentWs = start;

	std::priority_queue<std::pair<float, AstarNode*>, std::vector<std::pair<float, AstarNode*>>, std::greater<std::pair<float, AstarNode*>>> frontier;
	frontier.push(std::make_pair(0.f, startNode));

	std::vector<std::pair<AstarNode*, float>> costSoFar;
	costSoFar.push_back(std::make_pair(startNode, 0.f));

	AstarNode* nullNode;

	std::vector<std::pair<AstarNode*, AstarNode*>> cameFrom;
	cameFrom.push_back(std::make_pair(nullNode, startNode));
	
	while (!frontier.empty()){

		AstarNode* frontierNode = frontier.top().second;
		frontier.pop();
		
		for each (std::pair<int, GOAPAction*> action in actions)
		{
			AstarNode* current = new AstarNode();
			current->action = frontierNode->action;
			current->f = frontierNode->f;
			current->g = frontierNode->g;
			current->h = frontierNode->h;
			current->parentWs = frontierNode->parentWs;
			current->actualWs = frontierNode->actualWs;

			if (action.second->preconditions == current->parentWs) {
				
				current->action = action.second;
				current->actualWs = action.second->effects;

				if (current->actualWs == goal) {
					CalculatePlan(start, goal, cameFrom);
					firstIterNoPlan = false;
					return;
				}

				bool hasFoundIt = false;
				float newCost = 0;
				int foundIter = 0;

				/*for (int iter = 0; iter < costSoFar.size() && !hasFoundIt; iter++) {

					if (current->action == costSoFar[iter].first->action)
					{
						hasFoundIt = true;
						newCost = costSoFar[iter].second;
						foundIter = iter;
					}
				}*/

				if (dynamic_cast<GOAPAction_GoToObject*>(action.second) != NULL) {

					for each (Object * obj in simulatedAgent->getScene()->getKeyPositions()) {
						if (obj->index == action.second->preconditions.value.first) {
							simulatedAgent->setPosition(simulatedAgent->getScene()->getMaze()->cell2pix(obj->position));
						}
					}					
				}//if there were other actions, make agent met preconditions
				
				newCost += action.second->GetCost(simulatedAgent);
				printf_s("%f \n", newCost);

				AstarNode* newNode = new AstarNode();

				newNode->g = current->g + newCost;
				newNode->h = current->h + 1;
				newNode->f = newNode->g + newNode->h;

				newNode->parentWs = current->actualWs;

				/*if (newCost < costSoFar[foundIter].second)
				{
					costSoFar[foundIter].second = newCost;
					costSoFar[foundIter].first->g = newCost;
					costSoFar[foundIter].first->h = current->h + 1;
					costSoFar[foundIter].first->f = costSoFar[foundIter].first->g + costSoFar[foundIter].first->h;
					cameFrom[foundIter].first = current;

					frontier.push(std::pair<float, AstarNode*>(newCost + current->h, newNode));
				}*/

				costSoFar.push_back(std::make_pair(newNode, newCost));
				cameFrom.push_back(std::make_pair(current, newNode));
				frontier.push(std::pair<float, AstarNode*>(newNode->f, newNode));

			}

		}
		
	}

	firstIterNoPlan = true;
}