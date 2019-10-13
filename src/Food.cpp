#include "Food.h"
#include "Dependencies\freeglut\include\GL\freeglut.h"
 
 
int Food::getX() {
	return x;

}

int Food::getY() {
	return y;

}

//only the first time is spawned at 90,100
//after that position is random generated
Food::Food() : x(90),y(100) {
}

void Food::setX(int xx) {
	x = xx;
}

void Food::setY(int yy) {
	y = yy;
}

//draws the food and translate it to the appropriate coordinates
void Food::drawFood() {

	glLoadIdentity();
	glTranslatef(x, y, 0);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0 + food_size, 0);
	glVertex2f(0 + food_size, 0 + food_size);
	glVertex2f(0, 0 + food_size);
	glEnd();
}

std::vector<int> Food::getPosition() {
	std::vector<int> temp; 
	
	temp.push_back(x);
	temp.push_back(y);

	return temp;
}