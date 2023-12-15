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
#include "GOAP_Alg.h"

class SceneGOAP :
	public Scene
{
public:
	SceneGOAP();
	~SceneGOAP();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

private:
	void drawMaze();
	void drawCoin();
	void drawKey(int index);
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	SDL_Texture *keys_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
	bool loadCoinTextures(char* filename_key);

protected:
	bool canPlay = false;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;
};
