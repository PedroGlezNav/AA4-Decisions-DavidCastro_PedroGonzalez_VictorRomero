#include "SceneGOAP.h"

using namespace std;

SceneGOAP::SceneGOAP()
{
	draw_grid = false;
	maze = new Grid("../res/maze_rooms.csv");

	loadTextures("../res/maze_rooms.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Vector2D rand_cell(-1, -1);

	Vector2D coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3) || maze->getCellValue(coinPosition) == Colors::BLACK)
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	int roomType = maze->getCellValue(Vector2D((float)coinPosition.x, (float)coinPosition.y));

	coin = new Object(coinPosition, Colors::GOLD, roomType);

	loadCoinTextures("../res/keys.png");
	for (int iter = 0; iter < NUMBER_OF_COINS; iter++) {
		do {
			rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		} while ((!maze->isValidCell(rand_cell)));

		roomType = maze->getCellValue(Vector2D((float)rand_cell.x, (float)rand_cell.y));

		keyPositions.push_back(new Object(rand_cell, iter + Colors::RED, roomType));
	}

	graph = new Graph(maze->GetTerrain());

	std::vector<Object*> tempObj = keyPositions;

	tempObj.push_back(coin);

	Agent* agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agent->setPathCircleColor(255, 255, 0, 255);
	agent->setNavigationAlgorithm(new AStar_Alg);
	agent->setScene(this);
	do{
		rand_cell = Vector2D((float)(maze->getNumCellX() / 2), (float)(maze->getNumCellY() / 2));
	} while (!maze->isValidCell(rand_cell));

	agent->setPosition(maze->cell2pix(rand_cell));
	agent->setDecisionAlgorithm(new GOAP_Alg(tempObj, agent));
	agents.push_back(agent);


}

SceneGOAP::~SceneGOAP()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneGOAP::update(float dtime, SDL_Event *event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
			if (!canPlay) {
				printf_s("Playing simulation, press '2' to reset--------------------------------------\n\n");
				canPlay = true;
			}
		}
		break;
	default:
		break;
	}

	if (canPlay) {
		agents[0]->update(dtime, event);
	}
}

void SceneGOAP::draw()
{
	drawMaze();
	drawCoin();

	for (int iter = 0; iter < NUMBER_OF_COINS; iter++)
		drawKey(iter);

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for each (Agent * agent in agents)
	{
		agent->draw();
	}
}

const char* SceneGOAP::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SceneGOAP::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			switch (maze->getCellValue(Vector2D((float)i, (float)j)))
			{
			case Colors::WHITE:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 255);
				break;
			case Colors::BLACK:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 255);
				break;
			case Colors::RED:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 0, 0, 100);
				break;
			case Colors::ORANGE:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 94, 5, 100);
				break;
			case Colors::YELLOW:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 0, 100);
				break;
			case Colors::GREEN:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 255, 0, 100);
				break;
			case Colors::PINK:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 105, 180, 100);
				break;
			case Colors::BLUE:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 100);
				break;
			default:
				break;
			};
			coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
			rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
		}
	}
}

void SceneGOAP::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coin->position);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void SceneGOAP::drawKey(int index) {
	Vector2D key_coords = maze->cell2pix(keyPositions[index]->position);
	SDL_Rect srcrect = { index * sprite_w, 0, sprite_w, sprite_h };
	SDL_Rect dstrect = { (int)key_coords.x - (sprite_w / 2), (int)key_coords.y - (sprite_h / 2), sprite_w, sprite_h };
	SDL_Point center = { sprite_w / 2, sprite_h / 2 };
	SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), keys_texture, &srcrect, &dstrect, NULL, &center, SDL_FLIP_NONE);
}

bool SceneGOAP::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

bool SceneGOAP::loadCoinTextures(char* filename_key)
{
	SDL_Surface* image = IMG_Load(filename_key);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	keys_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = 6;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;

	if (image)
		SDL_FreeSurface(image);

	return true;
}
