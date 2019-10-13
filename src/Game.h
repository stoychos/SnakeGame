#pragma once
#include "Snake.h"
#include "Food.h"
#include <time.h>
#include <stdlib.h>


class Game {
	static Snake sn;
	static Food fd;
	static int exist;	 
	static void drawGrid();
	static void draw();
	static void init();
	static void reshape(int, int);
	static void timer(int);
	static std::vector<int> getRelativePosition(std::vector<int>, std::vector<int>, std::vector<int>);
	static void keyboardd(int key, int x, int y);
public:
	static const int grid_x_size = 200;
	static const int grid_y_size = 200;
	static int startGame(int argc, char **argv);
	static void drawScene();
	static Snake getSnake();
	static Food getFood();
	
	static std::vector<int> getState();
	
};

