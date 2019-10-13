#pragma once
#include <map>
#include <vector>
#include "Snake.h"
#include <random>
#include <fstream>

class Qtable {
	std::map<std::vector<int>, std::vector<double>> *qtable;
	double learningRate;
	double discountFactor;
public:
	Qtable();
	std::map<std::vector<int>, std::vector<double>>* getQtable();
	direction getBestAction(std::vector<double> actions);
	void updateTable(std::vector<int>, double oldValue, double maxValue, int direction, double reward);
	double maxValue(std::vector<double>);
	int getReallyRandom(int min, int high);
};