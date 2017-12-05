#pragma once
 
#include "Snake.h"
/*
getX() - get x coordinate
getY() - get y coordinate
setX() - assign the argument value to x
setY() - assign the argument value to y
generateRandom() - generate random number between 10 and 390
drawFood() - draws the food
Food(Snake*) - takes Snake as parameter to check if Food's coordinates collide with Snake coordinates when spawned 
*/


class Food {
	int x, y;
	static const int scale_size = 10;
	 
public:
	Food();
 
	void drawFood();
	int getX();
	int getY();
	void setX(int);
	void setY(int );
	 
 
};