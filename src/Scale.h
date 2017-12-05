#pragma once

/*
		Scale(int,int) - constructs a scale at the given coordinates
		getX() - returns x coordinate of the Scale
		getY() - returns y coordinate of the Scale
		drawScale() - draws a Scale and then translates it to the current coordinates 
		

*/


class Scale {
	int x;
	int y;
	static const int scale_size = 10;
public:
	Scale(int xx, int yy);
	int getX();
	int getY();

	void drawScale();
};