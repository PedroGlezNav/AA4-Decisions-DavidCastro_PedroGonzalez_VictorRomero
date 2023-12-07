#include "AStar_Alg.h"

std::vector<Vector2D> AStar_Alg::CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph, std::vector<Vector2D> enemyPositions)
{
	Graph tempGraph = *graph;
	tempGraph.ManhattanDistanceHeuristic(goalPos);
	if (enemyPositions.size() != 0) {
		tempGraph.AddEnemyHeuristic(enemyPositions);
	}

	nodesInFrontier = 0;

	std::priority_queue<std::pair<float, Vector2D>, std::vector<std::pair<float, Vector2D>>, std::greater<std::pair<float, Vector2D>>> frontier;
	frontier.push(std::make_pair(0.f, agentPos));

	std::vector<std::pair<Vector2D, float>> costSoFar;
	costSoFar.push_back(std::make_pair(agentPos, 0.f));

	std::vector<std::pair<Vector2D, Vector2D>> cameFrom;
	cameFrom.push_back(std::make_pair(NULL, agentPos));

	while (!frontier.empty())
	{
		if (frontier.top().second == goalPos) {
			return CalculatePath(agentPos, goalPos, cameFrom);
		}

		std::vector<Connection*> connections= tempGraph.GetConnectionsFromNode(frontier.top().second);
		frontier.pop();
		Vector2D neighbour;

		for each (Connection* frontierConnection in connections)
		{

			neighbour = frontierConnection->GetToNode()->GetPosition();

			bool hasFoundIt = false; 
			float newCost = 0;
			int foundIter = 0;

			for (int iter = 0; iter < costSoFar.size() && !hasFoundIt; iter++) {

				if (neighbour.x == costSoFar[iter].first.x && neighbour.y == costSoFar[iter].first.y) 
				{
					hasFoundIt = true; 
					newCost = costSoFar[iter].second;
					foundIter = iter;
				}
			}
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
		}
	}
}