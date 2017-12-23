#pragma once
#include <deque>
#include "Scale.h"

/*
	Snake(int ,int) - creates the snake at the given coordinates
	drawSnake() - draws the snake
	changeDirection(int dir) - turns the snake in the given direction
	move(int dir) - moves the snake one position in the given direction
	isHere(int x, int y) - checks if the snake is at the given coordinates 
	eatFood(int, int) - eats the food by adding one scale to the body
	hasCrashed() - checks if the snake collides with any of the edges of the screen
	isFoodFound(int, int) - checks if the snake encountered food
*/


enum direction {left =0,right,up,down};

class Snake {
	 
	std::deque<Scale*> python;
	 int direction_snake;
	 void addScale(int, int);
	 
	 void deleteScale();
	 static const int scale_size = 10;
	 static const int grid_x_size = 400;
	 static const int grid_y_size = 400;
	 bool collidesWithItself();
public:
	bool hasCrashed();
	int getDirection();
	Snake(int,int );
	void moveAuto();
	void drawSnake();
	void move(int dir);
    bool isHere(int x, int y);
	void eatFood(int x,int y);
	bool isFoodFound(int x, int y);
	 
};
