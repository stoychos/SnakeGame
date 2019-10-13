#include "Snake.h"
#include "Food.h"
#include "Dependencies\freeglut\include\GL\freeglut.h"
#include <time.h>


int Snake::died = 0;

void Snake::drawSnake() {
	for (int i = 0;i < python.size();i++) {
		glLoadIdentity();
		glColor3f(1, 0, 0);
		python[i].drawScale();
	}
	 
}
 
Snake::Snake(int xin,int yin) {
	srand(time(0));
	direction_snake = (direction)(rand() % (3 + 1));
	addScale(xin, yin);
	addScale(xin, yin);
	addScale(xin, yin);
	
}

void Snake::addScale(int xadd, int yadd) {
	Scale toAdd(xadd, yadd);
	python.push_back(toAdd);
}

bool Snake::isHere(int x, int y) {
	for (int i = 0;i < python.size();i++) {
		if (python[i].getX() == x && python[i].getY() == y)
			return true;
	}
	return false;

}

bool Snake::collidesWithItself() {
	for (int i = 4;i < python.size();i++) {
		if (python[0].getX() == python[i].getX() && python[0].getY() == python[i].getY())
			return true;
	}
	return false;

}

bool Snake::hasCrashed() {
	if (python[0].getX() == 0 || python[0].getY() == 0 || python[0].getX() == grid_x_size - 10 
		|| python[0].getY() == grid_y_size - 10) {
			return true;
	}
	if (collidesWithItself())
		return true;

	return false;

}
 

bool Snake::isFoodFound(int x, int y) {
	 if( getHeadPosition()[0] == x && getHeadPosition()[1] == y )
	   return true;

	return false;
	 
	 
}

void Snake::eatFood(int x, int y) {
	addScale(x,y);
}
 

int Snake::getDirection() {
	return direction_snake;
}

void Snake::moveAuto() {
	if (direction_snake == left)
		move(left);
	else if (direction_snake == right)
		move(right);
	else if (direction_snake == up)
		move(up);
	else
		move(down);
}

void Snake::deleteScale() {
	python.pop_back();
}


std::vector<int> Snake::move(int dir) {
	 
	int changeX = 0;
	int changeY = 0;
	 

		switch (dir) {
		case left:
			changeX -= scale_size;
			direction_snake = left;
			break;
		case right:
			changeX += scale_size;
			direction_snake = right;
			break;
		case up:
			changeY += scale_size;
			direction_snake = up;
			break;
		case down:
			changeY -= scale_size;
			direction_snake = down;
			break;
		}

		int newX = python[0].getX() + changeX;
		int newY = python[0].getY() + changeY;
		Scale toAdd(newX, newY);
		python.pop_back();
		python.push_front(toAdd);
	
		std::vector<int> temp;
		temp.push_back(python[0].getX());
		temp.push_back(python[1].getY());
	 
	return temp;
}

std::vector<int> Snake::getHeadPosition() {
	std::vector<int> temp;
	temp.push_back(python[0].getX());
	temp.push_back(python[0].getY());
	return temp;
}


std::vector<int> Snake::getTailPosition() {
	std::vector<int> temp;
	temp.push_back(python[python.size() - 1].getX());
	temp.push_back(python[python.size() - 1].getY());
	return temp;
}


void Snake::restartGame() {
	python.clear();
	addScale(100, 100);
	addScale(100, 100);
	addScale(100, 100);
	
}


void Snake::moveToDirection(direction dir) {
	switch (dir) {
	case 0:
		if (direction_snake == direction::right) {
			move(direction::right);
		}
		else {
			move(direction::left);
		}
		break;
	case 1:
		if (direction_snake == direction::left) {
			move(direction::left);
		}
		else {
			move(direction::right);
		}
		break;
	case 2:
		if (direction_snake == direction::down) {
			move(direction::down);
		}
		else {
			move(direction::up);
		}
		break;
	case 3:
		if (direction_snake == direction::up) {
			move(direction::up);
		}
		else {
			move(direction::down);
		}
		break;

	}
	
}

int Snake::getSize() {
	return python.size();
}

bool Snake::isThereDanger(int x, int y) {
	
	if (x == 0 || x == 190 || y == 0 || y == 190) {
		return true;
	}
	else if (isHere(x, y)) {
		return true;
	}
	return false;
}