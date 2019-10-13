#pragma once
#include <deque>
#include "Scale.h"
#include <vector>
 
enum direction {left =0,right,up,down};

class Snake {
	 
	std::deque<Scale> python;
	 int direction_snake;
	 void addScale(int, int);
	 
	 void deleteScale();
	 static const int scale_size = 10;
	 static const int grid_x_size = 200;
	 static const int grid_y_size = 200;
	 bool collidesWithItself();
	 friend class Game;
public:
	static int died;
	 
	bool hasCrashed();
	int getDirection();
	Snake(int,int );
	void moveAuto();
	void drawSnake();
	std::vector<int> move(int dir);
    bool isHere(int x, int y);
	void eatFood(int x,int y);
	bool isFoodFound(int x, int y);
	void moveToDirection(direction);
	std::vector<int> getTailPosition();
	std::vector<int> getHeadPosition();
	void restartGame();
	int getSize();
	bool isThereDanger(int, int);
};
