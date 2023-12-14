#include "SceneFSM.h"

using namespace std;

SceneFSM::SceneFSM()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent* agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agent->setPathCircleColor(255, 255, 0, 255);
	agent->setScene(this);
	agents.push_back(agent);

	for (int iter = 0; iter < NUMBER_OF_ENEMIES; iter++)
	{
		Agent* enemy = new Agent;
		enemy->loadSpriteTexture("../res/zombie1.png", 8);
		enemy->setBehavior(new PathFollowing);
		enemy->setTarget(Vector2D(-20, -20));
		enemy->setPathCircleColor(0, 0, 255, 50);
		enemy->setScene(this);
		enemy->setDecisionAlgorithm(new FSM_Alg);
		agents.push_back(enemy);
	}

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!maze->isValidCell(rand_cell)) {
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
	agents[0]->setPosition(maze->cell2pix(rand_cell));

	for (int iter = 1; iter < agents.size(); iter++)
	{
		rand_cell = Vector2D(-1, -1);
		while (!maze->isValidCell(rand_cell) || agents[0]->getPosition() == agents[iter]->getPosition()) {
			rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		}
		agents[iter]->setPosition(maze->cell2pix(rand_cell));
	}

	graph = new Graph(maze->GetTerrain());

}

SceneFSM::~SceneFSM()
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

void SceneFSM::update(float dtime, SDL_Event *event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
			canEnemiesBehaviour = !canEnemiesBehaviour;
			for (int iter = 1; iter < agents.size(); iter++){
				agents[iter]->clearPath();
			}
			printf_s("Booting up enemies--------------------------------------\n\n");
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
			agents[0]->setHasGun(!agents[0]->getHasGun());
			printf_s("Changing gun status--------------------------------------\n\n");
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			agents[0]->clearPath();
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				std::vector<Vector2D> pathPoints = agents[0]->getNavigationAlgorithm()->CalculatePathNodes(maze->pix2cell(agents[0]->getPosition()), cell, graph, std::vector<Vector2D>());
				for each (Vector2D point in pathPoints)
				{
					agents[0]->addPathPoint((maze->cell2pix(point)));
				}
			}
		}
		break;
	default:
		break;
	}

	for (int iter = 0; iter < agents.size(); iter++) {
		agents[iter]->update(dtime, event);
	}
}

void SceneFSM::draw()
{
	drawMaze();

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

const char* SceneFSM::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SceneFSM::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{		
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
		}
	}
}

bool SceneFSM::loadTextures(char* filename_bg, char* filename_coin)
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
