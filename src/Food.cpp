#include "Food.h"
#include "Dependencies\freeglut\freeglut.h"
 
 

int Food::getX() {
	return x;

}

int Food::getY() {
	return y;

}
 
//creates Food and iinitialize x and y - its coordinates
Food::Food() : x(180),y(200) {
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
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0 + scale_size, 0);
		glVertex2f(0 + scale_size, 0 + scale_size);
		glVertex2f(0, 0 + scale_size);
		glEnd();
			 

}