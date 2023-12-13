#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"
#include "Graph.h"

class Agent;

class Scene
{
protected:
	std::vector<Agent*> agents;
	bool canEnemiesBehaviour = false;
	Grid* maze;
	bool draw_grid;
	Graph* graph;

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

	Grid* getMaze() {
		return maze;
	}

	Graph* getGraph() {
		return graph;
	}
};

