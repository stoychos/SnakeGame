#pragma once
#include "Snake.h"
#include "Food.h"
#include <time.h>
#include <stdlib.h>

/*
initGame(int argc, char **argv) - initializes the game
drawScene() - renders the scene
getSnake() - returns the static member object Snake 
getFood() - returns the static member object Food
*/

class Game {
	static Snake sn;
	static Food fd;
	static int exist;
	static const int scale_size = 10;
	static const int grid_x_size = 400;
	static const int grid_y_size = 400;
	static void drawGrid();
	static void draw();
	static void init();
	static void reshape(int, int);
	static void timer(int);

	static void keyboardd(int key, int x, int y);
public:
	
	static int startGame(int argc, char **argv);
	static void drawScene();
	static Snake getSnake();
	static Food getFood();
	
	 
 
};

