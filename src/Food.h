#pragma once
 
#include "Snake.h"


class Food {
	int x, y;
	static const int food_size = 10;
	 
public:
	Food();
 
	void drawFood();
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	std::vector<int> getPosition();
 
};