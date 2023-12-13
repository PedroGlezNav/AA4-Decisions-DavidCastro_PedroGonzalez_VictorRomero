#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Vector2D.h"
#include <SDL.h>

#define SRC_WIDTH 1280
#define SRC_HEIGHT 768
#define CELL_SIZE 32

#define FRAMES_PER_SEC 30
#define MAX_DTIME 0.05

class Grid
{
public:
	Grid(char* filename);
	~Grid();

private:
	int num_cell_x;
	int num_cell_y;

	std::vector< std::vector<int> > terrain;

public:
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	int getCellValue(Vector2D cell);
	int getNumCellX();
	int getNumCellY();
	std::vector< std::vector<int> > GetTerrain();
};
