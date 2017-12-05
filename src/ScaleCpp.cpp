#include "Scale.h"
#include "Dependencies\freeglut\freeglut.h"


 


//creates a scale and initialize x and y with the arguments
Scale::Scale(int xx, int yy) : x(xx), y(yy) {

}

//returns x coordinate
int Scale::getX() {
	return x;

}

//returns y coordinate
int Scale::getY() {
	return y;
}
 

 //draws a scale and translate it to the actual coordinates
void Scale::drawScale() {

	glTranslatef(x, y, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0 + scale_size, 0);
	glVertex2f(0 + scale_size, 0 + scale_size);
	glVertex2f(0, 0 + scale_size);
	glEnd();
}