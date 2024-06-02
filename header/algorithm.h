#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <string>

using namespace std;

double evaluation();
void backwardElimination(int features);
void forwardSelection(int features);

void nearestNeighbor(vector<vector<double>> dataSet);
void validator();

vector<vector<double>> normalization(vector<vector<double>> dataSet);

#endif