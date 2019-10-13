#pragma once


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