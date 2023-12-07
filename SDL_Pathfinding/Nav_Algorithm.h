#pragma once
#include "Graph.h"

class Nav_Algorithm {
protected:
	int nodesInFrontier;
public:
	virtual std::vector<Vector2D> CalculatePathNodes(Vector2D agentPos, Vector2D goalPos, Graph* graph, std::vector<Vector2D> enemyPositions) = 0;

	std::vector<Vector2D> CalculatePath(Vector2D agentPos, Vector2D goalPos, std::vector<std::pair<Vector2D, Vector2D>> cameFrom)
	{
		Vector2D current = goalPos;
		std::vector<Vector2D> path;
		path.push_back(current);

		while (current != agentPos) {
			for each (std::pair<Vector2D, Vector2D> connection in cameFrom)
			{
				if (connection.second.x == current.x && connection.second.y == current.y) {
					current = connection.first;
					path.push_back(current);
				}
			}
		}

		std::reverse(path.begin(), path.end());
		return path;
	}

	int GetNodesInFrontier() {
		return nodesInFrontier;
	}
};