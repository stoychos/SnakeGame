#include "Qtable.h"
#include "Snake.h"
#include <iostream>

Qtable::Qtable() : learningRate(0.85),discountFactor(0.7) {
	qtable = new std::map<std::vector<int>, std::vector<double>>;
}


std::map<std::vector<int>, std::vector<double>>* Qtable::getQtable() {
	return qtable;
}

direction Qtable::getBestAction(std::vector<double> actions) {
	double max = -DBL_MAX;
	direction act;
	if (actions[0] > max) {
		max = actions[0];
		act = left;
	}
	if (actions[1] > max) {
		max = actions[1];
		act = right;
	}
	if (actions[2] > max) {
		max = actions[2];
		act = up;
	}
	if (actions[3] > max) {
		max = actions[3];
		act = down;
	}
	
	return act;
}


	void Qtable::updateTable(std::vector<int> position, double oldValue, double maxValue, int direction, double reward) {
		double newValue = oldValue + learningRate * (reward + (discountFactor*maxValue) - oldValue);
		qtable->at(position)[direction] = newValue;
		std::cout << "New value " << newValue << std::endl;
	}

	double Qtable::maxValue(std::vector<double> actions) {
		double max = -10000;
		if (actions[0] > max) {
			max = actions[0];
		}
		if (actions[1] > max) {
			max = actions[1];
		}
		if (actions[2] > max) {
			max = actions[2];
		}
		if (actions[3] > max) {
			max = actions[3];
		}

		return max;
	}


	int Qtable::getReallyRandom(int min, int max) {
		std::mt19937 rng(0);
		std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

		int r = gen(rng);
		return r;
	}