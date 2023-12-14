#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

#include "Scene.h"
#include "Seek.h"
#include "PathFollowing.h"

#include "BFS_Alg.h"
#include "Djikstra_Alg.h"
#include "Greedy_Alg.h"
#include "AStar_Alg.h"

#include "FSM_Alg.h"

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
	void drawMaze();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
};
