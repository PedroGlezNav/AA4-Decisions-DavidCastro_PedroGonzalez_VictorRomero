#include "Greedy_Alg.h"

std::vector<Vector2D> Greedy_Alg::CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph, std::vector<Vector2D> enemyPositions)
{
	Graph tempGraph = *graph;
	tempGraph.ManhattanDistanceHeuristic(goalPos);
	if (enemyPositions.size() != 0) {
		tempGraph.AddEnemyHeuristic(enemyPositions);
	}

	nodesInFrontier = 0;

	std::priority_queue<std::pair<float, Vector2D>, std::vector<std::pair<float, Vector2D>>, std::greater<std::pair<float, Vector2D>>> frontier;
	frontier.push(std::make_pair(0.f, agentPos));

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

			for (int iter = 0; iter < cameFrom.size() && !hasFoundIt; iter++)
			{
				if (neighbour.x == cameFrom[iter].second.x && neighbour.y == cameFrom[iter].second.y)
				{
					hasFoundIt = true;
				}
			}

			if (!hasFoundIt) 
			{
				cameFrom.push_back(std::make_pair(frontierConnection->GetFromNode()->GetPosition(), frontierConnection->GetToNode()->GetPosition()));
				frontier.push(std::pair<float, Vector2D>(frontierConnection->GetToNode()->GetHeuristic(), frontierConnection->GetToNode()->GetPosition()));

				//printf_s("New Frontier Point: (%f,%f) /// New Frontier Heuristic: (%f)\n", neighbour.x, neighbour.y, frontierConnection->GetToNode()->GetHeuristic());
				nodesInFrontier++;
			}
		}
	}
}