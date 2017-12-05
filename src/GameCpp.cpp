#include "Game.h"
#include "Dependencies\freeglut\freeglut.h"
#include <windows.h> 
#define FPS 10

//inital coordinates of the snake 200,200
Snake Game::sn(200, 200);

//initial coordinates of the food 180,200
Food Game::fd;

//initial value for exist
int Game::exist = 1;
 

//sets the viewport, projection matrix and modeview matrix
//set black as color for the color buffer
void Game::init() {
	glViewport(0, 0, 600, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Game::grid_x_size, 0, Game::grid_y_size, -1, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

}

//makes the window non resizable
void Game::reshape(int, int) {
	glutReshapeWindow(600, 600);

}


//timer callback function
void Game::timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}


//draws the game
//sets the back buffer for drawing
void Game::draw() {

 
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT);

	Game::drawScene();

	glutSwapBuffers();
}

//starts the game
//sets RGB mode and double buffering
//creates window with size 600x600
//calls draw function for rendering
//calls glutReshapeFunc if the window is reshaped
//gluSpecialFunc - keyboard listener
//registers the time callback function to be triggered in 1000/FPS milliseconds
int Game::startGame(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 20);
	glutCreateWindow("Snake Game");
	init();

	glutDisplayFunc(Game::draw);
	glutReshapeFunc(Game::reshape);
	glutSpecialFunc(Game::keyboardd);


	glutTimerFunc(1000 / FPS, timer, 0);


	glutMainLoop();
	return 0;


}


//draws the enclosure at the corner of the screen, the snake and the food
//checks if the snake collides with itself or the end of the screen
//if the food is eaten, new coordinates are generated, otherwise draws it at the same position 
void Game::drawScene() {
	srand(time(0));
	drawGrid();

	sn.drawSnake();

	if (sn.hasCrashed()) {
		MessageBox(NULL, L"LOOSER", L"GAME OVER",
			0);
		exit(0);
	}

	if (sn.isFoodFound(fd.getX(), fd.getY())) {
		sn.eatFood(fd.getX(), fd.getY());
		exist = 0;
	}
	 
 	
	if (exist == 0) {
		 
		fd.setX((rand() % 38 + 1) * 10);
		fd.setY((rand() % 38 + 1) * 10);
	}

	//checks if the snake is at the coordinates where the food will be spawned
	if (!sn.isHere(fd.getX(), fd.getY())) {
		fd.drawFood();
		exist = 1;
	}
		sn.moveAuto();


 
}

 
//keyboard listener
void Game::keyboardd(int key, int x, int y) {

	switch (key) {

	case GLUT_KEY_LEFT:
		if (sn.getDirection() != right && sn.getDirection() != left)
			sn.move(direction::left);

		break;
	case GLUT_KEY_UP:
		if (sn.getDirection() != down && sn.getDirection() != up)
			sn.move(direction::up);

		break;
	case GLUT_KEY_RIGHT:
		if (sn.getDirection() != left && sn.getDirection() != right)
			sn.move(direction::right);
		break;

	case GLUT_KEY_DOWN:
		if (sn.getDirection() != up && sn.getDirection() != down)
			sn.move(direction::down);
		break;
	}


}

//draws the enclosure at the corners of the screen
void Game::drawGrid() {

	for (int i = 0;i < grid_x_size;i++) {
		for (int j = 0;j < grid_y_size;j++) {


			if (i == 0 || j == 0 || i == grid_x_size - 10 || j == grid_y_size - 10) {
				glLoadIdentity();
				glColor3f(1, 0, 0);
				glBegin(GL_QUADS);
				glVertex2f(i, j);
				glVertex2f(i + 10, j);
				glVertex2f(i + 10, j + 10);
				glVertex2f(i, j + 10);
				glEnd();
			}


		}
	}
}

//returns the snake
Snake Game::getSnake() {
	return sn;

}

//returns the food
Food Game::getFood() {
	return fd;
}

 