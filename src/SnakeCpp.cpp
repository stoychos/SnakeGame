#include "Snake.h"
#include "Food.h"
#include "Dependencies\freeglut\freeglut.h"



 //draws the snake by drawing each of its scales 
// and restart the matrix after each one so that the next scales are rendered appropriately
void Snake::drawSnake() {
	for (int i = 0;i < python.size();i++) {
		glLoadIdentity();
		glColor3f(1, 0, 0);
		python[i]->drawScale();
	}
	 
}
 

//constructs the snake by creating a scale at the given coordinates 
Snake::Snake(int xin,int yin)  : direction_snake(right)  {
	addScale(xin, yin);
	addScale(xin + 10, yin);
	addScale(xin + 20, yin);
}


//expands the length of the snake by adding another scale 
// invoked by constructing and eating food 
void Snake::addScale(int xadd, int yadd) {
	Scale* toAdd = new Scale(xadd, yadd);
	python.push_back(toAdd);
}


//checks if the snake is at the given coordinates by comparing them with those on each scale 
//if they coincide, returns true, otherwise false
bool Snake::isHere(int x, int y) {
	for (int i = 0;i < python.size();i++) {
		if (python[i]->getX() == x && python[i]->getY() == y)
			return true;
	}
	return false;

}

//checks if the snake collides with itself
bool Snake::collidesWithItself() {
	for (int i = 4;i < python.size();i++) {
		if (python[0]->getX() == python[i]->getX() && python[0]->getY() == python[i]->getY())
			return true;
	}
	return false;

}

//checks if the snake collides with itself or goes out of the rendered scope
bool Snake::hasCrashed() {
	if (python[0]->getX() == 0 || python[0]->getY() == 0 || python[0]->getX() == grid_x_size - 10 || python[0]->getY() == grid_y_size - 10) {
		return true;
	}
	if (collidesWithItself())
		return true;

	return false;

}
 

//check if the snake found the food at the given coordinates x and y
bool Snake::isFoodFound(int x, int y) {
	if (isHere(x, y))
	 
	return true;

	return false;
	 
	 
}

//eats the food at coordinates x and y
//adds the food as another scale to the snake
void Snake::eatFood(int x, int y) {
	addScale(x,y);
}
 

//gets the current direction of the snake
int Snake::getDirection() {
	return direction_snake;
}

//the snake moves in the current direction automatic
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

//deletes the last scale of the snake
void Snake::deleteScale() {
	python.pop_back();
}


//move the snake one position in the given direction 
void Snake::move(int dir) {
	 
	int changeX = 0;
	int changeY = 0;
	 
	//checks the current direction
	//if direction is left, x is decreased, y remains the same
	//if direction is right, x is increased, y remains the same 
	//if direction is up, y is increased, x remains the same 
	//if direction is down, y is decreased, x remains the same
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

		//adds new scale with the temporary x and y as coordinates and deletes the last scale
		int newX = python[0]->getX() + changeX;
		int newY = python[0]->getY() + changeY;
		Scale* toAdd = new Scale(newX, newY);
		python.pop_back();
		python.push_front(toAdd);
		 
	 
	 
}
