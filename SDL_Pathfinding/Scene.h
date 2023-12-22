#pragma once
#include <iostream>
#include <unordered_map>

#include "Grid.h"
#include "Graph.h"

class Agent;

enum Colors
{
	WHITE, BLACK, RED, ORANGE, YELLOW, GREEN, PINK, BLUE, GOLD
};

class Object {
public:
	Vector2D position;
	int index;
	int roomType;

	Object(Vector2D newPos, int newIndex, int newRoomIndex) {

		position = newPos;
		index = newIndex;
		roomType = newRoomIndex;
	};
};

class Scene
{
protected:
	std::vector<Agent*> agents;
	bool canEnemiesBehaviour = false;
	Grid* maze;
	bool draw_grid;
	Graph* graph;
	Object* coin;
	std::vector<Object*> keyPositions;

public:
	Scene() {};
	virtual ~Scene() {};
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };

	std::vector<Agent*> GetAgents() {
		return agents;
	}

	bool getCanEnemiesBehaviour() {
		return canEnemiesBehaviour;
	}

	void setCanEnemiesBehaviour(bool newCanEnemiesBehaviour) {
		canEnemiesBehaviour = newCanEnemiesBehaviour;
	}

	std::vector<Object*> getKeyPositions() {
		return keyPositions;
	}

	Grid* getMaze() {
		return maze;
	}

	Graph* getGraph() {
		return graph;
	}
};

