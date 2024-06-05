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
    Classifier (vector<vector<double>> trainSet){this->trainSet = trainSet;}; //This is eht train function since this is a class
    // void Train(vector<vector<double>> trainSet); 
    int test(vector<double> testInstance, vector<int> featureSubset); //returns the predicted class label of testInstance; is the n.n. alg
};

double evaluation();
vector<int> backwardElimination(int features);
set<int> forwardSelection(int features);

// void nearestNeighbor(vector<vector<double>> dataSet);
double validator(vector<int> featureSubset, vector<vector<double>> dataSet);

vector<vector<double>> normalization(vector<vector<double>> dataSet);
double calculateEuclidDistance(vector<double>& training, vector<double>& testing, vector<int>& features);
//double calculateEuclidDistance(vector<double>& training, vector<double>& testing);
#endif