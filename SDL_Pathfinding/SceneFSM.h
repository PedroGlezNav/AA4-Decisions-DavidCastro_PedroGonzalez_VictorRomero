#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "Graph.h"

#include "BFS_Alg.h"
#include "Djikstra_Alg.h"
#include "Greedy_Alg.h"
#include "AStar_Alg.h"

class SceneFSM :
	public Scene
{
public:
	SceneFSM();
	~SceneFSM();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;

	Grid *maze;
	bool draw_grid;

	Graph* graph;

	Nav_Algorithm* nav_Algorithm;
	Nav_Algorithm* enemies_Nav_Algorithm;
		
	void drawMaze();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
