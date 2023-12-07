#include "BFS_Alg.h"

std::vector<Vector2D> BFS_Alg::CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph, std::vector<Vector2D> enemyPositions)
{
	nodesInFrontier = 0;

	std::queue<Vector2D> frontier;
	frontier.push(agentPos);

	std::vector<std::pair<Vector2D, Vector2D>> cameFrom;
	cameFrom.push_back(std::make_pair(NULL, agentPos));

	while (!frontier.empty())
	{
		if (frontier.front() == goalPos) {
			return CalculatePath(agentPos, goalPos, cameFrom);
		}

		std::vector<Connection*> connections= graph->GetConnectionsFromNode(frontier.front());
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

			if (!hasFoundIt) {
				cameFrom.push_back(std::make_pair(frontierConnection->GetFromNode()->GetPosition(), frontierConnection->GetToNode()->GetPosition()));
				frontier.push(neighbour);
				//printf_s("New Frontier Point: (%f,%f)\n", neighbour.x, neighbour.y);
				nodesInFrontier++;
			}
		}
	}
}