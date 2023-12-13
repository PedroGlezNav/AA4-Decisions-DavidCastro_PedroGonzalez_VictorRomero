#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

#include "Scene.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "Graph.h"

#include "BFS_Alg.h"
#include "Djikstra_Alg.h"
#include "Greedy_Alg.h"
#include "AStar_Alg.h"

class SceneExercise2 :
	public Scene
{
public:
	SceneExercise2();
	~SceneExercise2();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D initialAgent0Pos;

	Grid *maze;
	bool draw_grid;

	Graph* graph;

	bool canEnemiesBehaviour = false;

	Nav_Algorithm* nav_Algorithm;
	Nav_Algorithm* enemies_Nav_Algorithm;
		
	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
