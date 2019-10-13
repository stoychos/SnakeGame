#include "Game.h"
#include "D:\дипломна\AI-snake\freeglut\include\GL\freeglut.h"
#include <windows.h>
#include <map>
#include <vector>
#include "Qtable.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <chrono>

#define BOOLEANS
#define FPS 25

Snake Game::sn(100, 100);
Food Game::fd;

int Game::exist = 1;

int max_points = 0;

Qtable qtable;

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

void Game::reshape(int, int) {
	glutReshapeWindow(600, 600);

}

void Game::timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

//sets the back buffer for drawing
void Game::draw() {
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT);

	Game::drawScene();

	glutSwapBuffers();
}


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

void Game::drawScene() {
	direction best_direction;
	double reward = 0;
	int flag = 0;
	int randn;
	std::vector<int> current_state;
	std::map<std::vector<int>, std::vector<double>>::iterator it_current_state;
	std::vector<int> new_state;
	std::map<std::vector<int>, std::vector<double>>::iterator it_new_state;

	srand(time(0));
	drawGrid();
	if (sn.getSize() > max_points)
		max_points = sn.getSize();

	 
	randn = rand() % (3 + 1);
	
	best_direction = (direction)randn;

	 
	sn.drawSnake();
	
	current_state = getState();
	
	it_current_state = qtable.getQtable()->find(current_state);

	if (it_current_state != qtable.getQtable()->end()) {
		
		best_direction = qtable.getBestAction(it_current_state->second);
		//std::cout << "Best direction: " << best_direction << std::endl;
		 
		flag = 1;
	}
	else {
		qtable.getQtable()->insert(std::pair<std::vector<int>, std::vector<double>>(current_state, std::vector<double>(current_state.size(), 0)));
	}
	   
	if (sn.hasCrashed()) {
			reward = -1;
			sn.restartGame();

			Snake::died++;
			std::cout << "Died : " << Snake::died << std::endl;
			std::cout << "MAX POINTS " << max_points << std::endl;
	}
	
	
	while (true) {
		if (!sn.isHere(fd.getX(), fd.getY())) {
			fd.drawFood();
			exist = 1;
			break;
		}
		else {
			fd.setX((rand() % 18 + 1) * 10);
			fd.setY((rand() % 18 + 1) * 10);
		}
	}
 
	if (sn.isFoodFound(fd.getX(), fd.getY())) {
		sn.eatFood(fd.getX(), fd.getY());
		exist = 0;
		reward = 1;
	}

	if (reward == 0) {
		reward = -0.1;
	}
 
	sn.moveToDirection(best_direction);

	new_state = getState();
	it_new_state = qtable.getQtable()->find(new_state);

	if (it_new_state != qtable.getQtable()->end()) {
		qtable.updateTable(current_state, qtable.getQtable()->at(current_state)[best_direction], qtable.maxValue(it_new_state->second), best_direction, reward);
	}
	else {
		qtable.updateTable(current_state, qtable.getQtable()->at(current_state)[best_direction], 0, best_direction, reward);	
	}

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

Snake Game::getSnake() {
	return sn;

}

Food Game::getFood() {
	return fd;
}


std::vector<int> Game::getRelativePosition(std::vector<int> head, std::vector<int> food, std::vector<int> tail) {
	std::vector<int> diff;
	int x_head_food = food[0] - head[0];
	int y_head_food = food[1] - head[1];

	diff.push_back(x_head_food);
	diff.push_back(y_head_food);

	int x_head_tail = tail[0] - head[0];
	int y_head_tail = tail[1] - head[1];

	diff.push_back(x_head_tail);
	diff.push_back(y_head_tail);

	return diff;

}

std::vector<int> Game::getState() {
	std::vector<int> current_state;


#ifdef BOOLEANS
	bool left = false, right = false, straight = false;
	if (sn.getDirection() == 0) {
		if (sn.isThereDanger(sn.getHeadPosition()[0] - 10, sn.getHeadPosition()[1])) {
			straight = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0], sn.getHeadPosition()[1] - 10)) {
			left = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0], sn.getHeadPosition()[1] + 10)) {
			right = true;
		}
	}
	else if (sn.getDirection() == 1) {
		if (sn.isThereDanger(sn.getHeadPosition()[0] + 10, sn.getHeadPosition()[1])) {
			straight = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0], sn.getHeadPosition()[1] + 10)) {
			left = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0], sn.getHeadPosition()[1] - 10)) {
			right = true;
		}
	}
	else if (sn.getDirection() == 2) {
		if (sn.isThereDanger(sn.getHeadPosition()[0], sn.getHeadPosition()[1]) + 10) {
			straight = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0] - 10, sn.getHeadPosition()[1])) {
			left = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0] + 10, sn.getHeadPosition()[1])) {
			right = true;
		}
	}
	else {
		if (sn.isThereDanger(sn.getHeadPosition()[0], sn.getHeadPosition()[1]) - 10) {
			straight = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0] + 10, sn.getHeadPosition()[1])) {
			left = true;
		}
		if (sn.isThereDanger(sn.getHeadPosition()[0] - 10, sn.getHeadPosition()[1])) {
			right = true;
		}
	}

	current_state.push_back(left);
	current_state.push_back(right);
	current_state.push_back(straight);
	
	
	if (sn.getDirection() == 0) {
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(0);
	}else if (sn.getDirection() == 1) {
		current_state.push_back(0);
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(0);
	}else if (sn.getDirection() == 2) {
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(1);
		current_state.push_back(0);
	}else {
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(1);
	}

	if (sn.getHeadPosition()[0] < fd.getX() && sn.getHeadPosition()[1] < fd.getY()) {
			current_state.push_back(0);
			current_state.push_back(1);
			current_state.push_back(1);
			current_state.push_back(0);
		}
	else if (sn.getHeadPosition()[0] > fd.getX() && sn.getHeadPosition()[1] < fd.getY()) {
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(1);
		current_state.push_back(0);
	}
	else if (sn.getHeadPosition()[1] > fd.getY() && sn.getHeadPosition()[0] < fd.getX()) {
		current_state.push_back(0);
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(1);
	}
	else if (sn.getHeadPosition()[1] > fd.getY() && sn.getHeadPosition()[0] > fd.getX()) {
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(1);
	}
	else if(sn.getHeadPosition()[1] == fd.getY() && sn.getHeadPosition()[0] < fd.getX()) {
		current_state.push_back(0);
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(0);
	}
	else if (sn.getHeadPosition()[0] == fd.getX() && sn.getHeadPosition()[1] < fd.getY()) {
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(1);
		current_state.push_back(0);
	}
	else if (sn.getHeadPosition()[1] == fd.getY() && sn.getHeadPosition()[0] > fd.getX()) {
		current_state.push_back(1);
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(0);
	}
	else if (sn.getHeadPosition()[0] == fd.getX() && sn.getHeadPosition()[1] > fd.getY()) {
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(1);
	}
	else {
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(0);
		current_state.push_back(0);
	}
#endif // BOOLEANS

	return current_state;
}
