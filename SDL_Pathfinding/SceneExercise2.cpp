#include "SceneExercise2.h"

using namespace std;

SceneExercise2::SceneExercise2()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20,-20));
	agent->setPathCircleColor(255, 255, 0, 255);
	agents.push_back(agent);

	for (int iter = 0; iter < 7; iter++) 
	{
		Agent* enemy = new Agent;
		enemy->loadSpriteTexture("../res/zombie1.png", 8);
		enemy->setBehavior(new PathFollowing);
		enemy->setTarget(Vector2D(-20, -20));
		enemy->setPathCircleColor((rand() % 255), (rand() % 255), (rand() % 255), 50);
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
	initialAgent0Pos = agents[0]->getPosition();

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	graph = new Graph(maze->GetTerrain());
	nav_Algorithm = new Greedy_Alg();
	printf_s("Breadth-First Search--------------------------------------\n\n");

	enemies_Nav_Algorithm = new BFS_Alg();
}

SceneExercise2::~SceneExercise2()
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

void SceneExercise2::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
			draw_grid = !draw_grid;
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_S && agents[0]->getPathSize() == 0) {

			canEnemiesBehaviour = true;
			std::vector<Vector2D> pathPoints = nav_Algorithm->CalculatePathNodes(maze->pix2cell(agents[0]->getPosition()), coinPosition, graph, std::vector<Vector2D>());
			for each (Vector2D point in pathPoints)
			{
				agents[0]->addPathPoint(maze->cell2pix(point));
			}
			printf_s("Number of nodes in frontier: %d ----------------------------------\n\n", nav_Algorithm->GetNodesInFrontier());
		}

		if (event->key.keysym.scancode == SDL_SCANCODE_R && agents[0]->getPathSize() == 0) {
			agents[0]->setPosition(initialAgent0Pos);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT && agents[0]->getPathSize() == 0)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				coinPosition = cell;
			}
		}
		break;
	default:
		break;
	}

	for (int iter = 1; iter < agents.size(); iter++)
	{
		if (agents[iter]->getPathSize() == 0 && canEnemiesBehaviour) {
			Vector2D rand_cell = Vector2D(-1, -1);
			while (!maze->isValidCell(rand_cell)) {
				rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			}
			std::vector<Vector2D> pathPoints = enemies_Nav_Algorithm->CalculatePathNodes(maze->pix2cell(agents[iter]->getPosition()), rand_cell, graph, std::vector<Vector2D>());
			for each (Vector2D point in pathPoints)
			{
				agents[iter]->addPathPoint(maze->cell2pix(point));
			}
		}

		float dist = Vector2D::Distance(maze->pix2cell(agents[iter]->getPosition()), maze->pix2cell(agents[0]->getPosition()));
		if (dist < PLAYER_ENEMY_RADIUS && canEnemiesBehaviour && agents[0]->getPathSize() != 0) {
			printf_s("Realculating route\n\n");
			agents[0]->clearPath();

			std::vector<Vector2D> enemyPositions;
			for (int iter2 = 1; iter2 < agents.size(); iter2++) {
				enemyPositions.push_back(maze->pix2cell(agents[iter2]->getPosition()));
			}

			std::vector<Vector2D> pathPoints = nav_Algorithm->CalculatePathNodes(maze->pix2cell(agents[0]->getPosition()), coinPosition, graph, enemyPositions);
			for each (Vector2D point in pathPoints)
			{
				agents[0]->addPathPoint(maze->cell2pix(point));
			}
			printf_s("Number of nodes in frontier: %d ----------------------------------\n\n", nav_Algorithm->GetNodesInFrontier());
		}
	}

	for (int iter = 0; iter < agents.size(); iter++)
	{
		agents[iter]->update(dtime, event);
	}
}

void SceneExercise2::draw()
{
	drawMaze();
	drawCoin();

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

	for each (Agent* agent in agents)
	{
		agent->draw();
	}
}

const char* SceneExercise2::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SceneExercise2::drawMaze()
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
			} else {
				// Do not draw if it is not necessary (bg is already black)
			}
					
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneExercise2::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool SceneExercise2::loadTextures(char* filename_bg, char* filename_coin)
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
