#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Classifier{
private: 
    vector<vector<double>> trainSet;
public:
    Classifier (vector<vector<double>> trainSet){this->trainSet = trainSet;}; //This is the train function since this is a class
    int test(vector<double> testInstance, vector<int> featureSubset); //returns the predicted class label of testInstance; is the n.n. alg
};

double evaluation();
vector<int> backwardElimination(int features);
vector<int> forwardSelection(int features);

double validator(vector<int> featureSubset, vector<vector<double>> dataSet);

vector<vector<double>> normalization(vector<vector<double>> dataSet);
double calculateEuclidDistance(vector<double>& training, vector<double>& testing, vector<int>& features);

#endif