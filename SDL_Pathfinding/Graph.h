#pragma once

#include "Connection.h"

class Graph {
private:
	std::vector<Connection*> connections;

public:
	Graph(std::vector<std::vector<int>> grid_terrain){
		for (int i = 0; i < grid_terrain.size(); i++) {
			for (int j = 0; j < grid_terrain[i].size(); j++) {
				if (grid_terrain[i][j] == 1) {

					Node* newFromNode = new Node(0, Vector2D(j, i));

					//Left
					if (i - 1 > 0 && grid_terrain[i - 1][j] == 1) {
						Node* newToNodeLeft = new Node(0, Vector2D(j, i - 1));
						Connection *newConnection = new Connection(randomFloat(0, 10), newFromNode, newToNodeLeft);
						connections.push_back(newConnection);
					}
					//Right
					if (i + 1 < grid_terrain.size() && grid_terrain[i + 1][j] == 1) {
						Node* newToNodeRight = new Node(0, Vector2D(j, i + 1));
						Connection* newConnection = new Connection(randomFloat(0, 10), newFromNode, newToNodeRight);
						connections.push_back(newConnection);
					}
					//Down
					if (j + 1 < grid_terrain[i].size() && grid_terrain[i][j + 1] == 1) {
						Node* newToNodeDown = new Node(0, Vector2D(j + 1, i));
						Connection* newConnection = new Connection(randomFloat(0, 10), newFromNode, newToNodeDown);
						connections.push_back(newConnection);
					}
					//Up
					if (j - 1 > 0 && grid_terrain[i][j - 1] == 1) {
						Node* newToNodeUp = new Node(0, Vector2D(j - 1, i));
						Connection* newConnection = new Connection(randomFloat(0, 10), newFromNode, newToNodeUp);
						connections.push_back(newConnection);
					}
				}
			}
		}
	}

	std::vector<Connection*> GetConnectionsFromNode(Vector2D fromNode) {

		std::vector<Connection*> fromNodeConnections;

		for (int iter = 0; iter < connections.size(); iter++) {
			if (connections[iter]->GetFromNode()->GetPosition().x == fromNode.x && connections[iter]->GetFromNode()->GetPosition().y == fromNode.y) {
				fromNodeConnections.push_back(connections[iter]);
			}
		}

		return fromNodeConnections;
	}

	void ManhattanDistanceHeuristic(Vector2D goalNode) {
		for (int i = 0; i < connections.size(); i++)
		{
			float fromNodeNewHeur = abs(connections[i]->GetFromNode()->GetPosition().x - goalNode.x) + abs(connections[i]->GetFromNode()->GetPosition().y - goalNode.y);
			connections[i]->GetFromNode()->SetHeuristic(fromNodeNewHeur);
			float toNodeNewHeur = abs(connections[i]->GetToNode()->GetPosition().x - goalNode.x) + abs(connections[i]->GetToNode()->GetPosition().y - goalNode.y);
			connections[i]->GetToNode()->SetHeuristic(toNodeNewHeur);
		}
	}

	void AddEnemyHeuristic(std::vector<Vector2D> enemyPositions) {

		std::vector<Connection*> tempConnections = connections;

		for (int i = 0; i < enemyPositions.size(); i++) {
			for (int j = 0; j < connections.size(); j++) {

				float fromNodeDist = Vector2D::Distance(connections[j]->GetFromNode()->GetPosition(), enemyPositions[i]);
				if (fromNodeDist < PLAYER_ENEMY_RADIUS) {
					float newHeuristic = connections[j]->GetFromNode()->GetHeuristic() + (ENEMY_HEURISTIC_ADDITIVE - fromNodeDist);
					connections[j]->GetFromNode()->SetHeuristic(newHeuristic);
				}

				float toNodeDist = Vector2D::Distance(connections[j]->GetToNode()->GetPosition(), enemyPositions[i]);
				if (toNodeDist < PLAYER_ENEMY_RADIUS) {
					float newHeuristic = connections[j]->GetToNode()->GetHeuristic() + (ENEMY_HEURISTIC_ADDITIVE - toNodeDist);
					connections[j]->GetToNode()->SetHeuristic(newHeuristic);
				}
			}
		}
	}

	float randomFloat()
	{
		return (float)(rand()) / (float)(RAND_MAX);
	}

	int randomInt(int a, int b)
	{
		if (a > b)
			return randomInt(b, a);
		if (a == b)
			return a;
		return a + (rand() % (b - a));
	}

	float randomFloat(int a, int b)
	{
		if (a > b)
			return randomFloat(b, a);
		if (a == b)
			return a;

		return (float)randomInt(a, b) + randomFloat();
	}
};