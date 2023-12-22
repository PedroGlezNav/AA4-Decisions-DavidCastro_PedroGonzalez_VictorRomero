#include "GOAP_Alg.h"

std::vector<GOAPAction*> GOAP_Alg::CalculatePath(GOAPWorldState start, GOAPWorldState goal)
{

}

GOAP_Alg::GOAP_Alg(std::vector<Object*> object)
{
	for each (Object * newObject in object)
	{
		GOAPAction* action = new GOAPAction_GoToObject(newObject);
		actions.insert(std::pair<int, GOAPAction*>(newObject->index, action));
	}
}

void GOAP_Alg::Update(Agent* agent, float dtime)
{
	

	/*
	if (plan.empty()) AStar();
	else {

	}*/
}

void GOAP_Alg::AStar(GOAPWorldState start, GOAPWorldState goal)
{

	AstarNode startNode;

	startNode.actualWs = start;

	std::priority_queue<std::pair<float, AstarNode>, std::vector<std::pair<float, AstarNode>>, std::greater<std::pair<float, AstarNode>>> frontier;
	frontier.push(std::make_pair(0.f, startNode));

	std::vector<std::pair<AstarNode, float>> costSoFar;
	costSoFar.push_back(std::make_pair(startNode, 0.f));

	AstarNode nullNode;

	std::vector<std::pair<AstarNode, AstarNode>> cameFrom;
	cameFrom.push_back(std::make_pair(nullNode, startNode));

	while (!frontier.empty()){

		AstarNode current = frontier.top().second;
		frontier.pop();

		if (current.actualWs == goal) {
			CalculatePath(start, goal);
			return;
		}
		
		for each (std::pair<int, GOAPAction*> action in actions)
		{
			if (action.second->preconditions == current.actualWs) {
				/*
				newCost += frontierConnection->GetCost();

				if (!hasFoundIt)
				{
					costSoFar.push_back(std::make_pair(frontierConnection->GetToNode()->GetPosition(), newCost));
					cameFrom.push_back(std::make_pair(frontierConnection->GetFromNode()->GetPosition(), frontierConnection->GetToNode()->GetPosition()));
					frontier.push(std::pair<float, Vector2D>(newCost + frontierConnection->GetToNode()->GetHeuristic(), frontierConnection->GetToNode()->GetPosition()));

					//printf_s("New Frontier Point: (%f,%f) /// New Frontier Heuristic Function: (%f)\n", neighbour.x, neighbour.y, newCost);
					nodesInFrontier++;
				}
				else if (newCost < costSoFar[foundIter].second)
				{
					costSoFar[foundIter].second = newCost;
					cameFrom[foundIter].first = frontierConnection->GetFromNode()->GetPosition();
					frontier.push(std::pair<float, Vector2D>(newCost + frontierConnection->GetToNode()->GetHeuristic(), frontierConnection->GetToNode()->GetPosition()));

					//printf_s("New Frontier Point: (%f,%f) /// New Frontier Heuristic Function: (%f)\n", neighbour.x, neighbour.y, newCost);
					nodesInFrontier++;
				}
				*/
			}


		}
		
	}

}