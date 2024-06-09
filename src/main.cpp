#include "../header/algorithm.h"
#include <set>
#include <fstream>
#include <sstream>

vector<vector<double>> getData(string& filename);
int numFeatures(vector<vector<double>> dataSet);

int main() {
    
    std::vector<double> accuracy;
    int userInput; 
    string file;
    int features;

    //ask user for what file they want to run
    cout << "\n\nWelcome to the Feature Selection Algorithm \n";
    cout << "-------------------------------------------\n";
    cout << "Which file would you like to test? (enter 1-4)\n";
    cout << "1. small-test-dataset from phase 2\n";
    cout << "2. large-test-dataset from phase 2\n";
    cout << "3. personal small-test-dataset #43\n";
    cout << "4. pesonal large-test-dataset  #43\n";
    
    
    do{
        cin >> userInput;
        if(cin.fail()){
            cout << "\nEnter a number between 1-4:\n";
            cin.clear();
            cin.ignore(10000 , '\n');
        }

        if(userInput > 4 || userInput <=0){
            cout << "\nEnter a number between 1-4:\n";
        }

        
    } while(userInput <= 0 || userInput >4);


    switch(userInput){
        case 1: file = "./txt/small-test-dataset.txt"; break;
        case 2: file = "./txt/large-test-dataset.txt"; break;
        case 3: file = "./txt/CS170_Spring_2024_Small_data__43.txt"; break;
        case 4: file = "./txt/CS170_Spring_2024_Large_data__43.txt"; break;
    }


    //first normalize the dataset.
    vector<vector<double>> dataSet = getData(file);
    vector<vector<double>> normalizedData = normalization(dataSet);//use normalized data 

    //get number of features in the dataset
    features = numFeatures(normalizedData);

  
    cout << " \n";
    //testing
    //  cout << file << endl; 


    int userChoice;
    cout << "Type the number of the algorithm you want to run(1-3): \n";
    cout << "1. Forward Selection \n";
    cout << "2. Backward Elimination \n";
    cout << "3. Choose your own features \n";
    do{
        cin >> userChoice;
        if(cin.fail()){
            
            cin.clear();
            cin.ignore(10000 , '\n');
            
        }
        

    } while(userChoice != 1 && userChoice !=2 && userChoice !=3);
    cout << " \n\n\n";


    vector<int> featureSubset;
    if(userChoice == 1)
    {
        featureSubset = forwardSelection(features, normalizedData);  
    }
    else if(userChoice == 2)
    {
        featureSubset = backwardElimination(features, normalizedData);
    }
    else if(userChoice == 3){
        cout << "Please enter each feature (enter 0 to stop):" << endl;
        int input = -1;
        while(input != 0){
            cin >> input;
            if(input == 0){
                cout << "Finished making feature set:" << endl;
            }
            else{
                featureSubset.push_back(input);
            }
        }
        for(int i = 0; i < featureSubset.size(); i++){
                cout << featureSubset[i] << " ";
        }
        cout << endl;
    }

    // vector <double> test;
    // double x;
    // cout << "Please enter test instance, separate feature values by space (ex: 0.1 0.6 0.7): ";
    //     // while (cin >> in) {
    //     //     test.push_back(in);
    //     // }
    // for(int i = 0; i < userInput; i++){
    //     cin >> x;
    //     test.push_back(x);
    // }

    // Classifier nn = Classifier(normalizedData); //This is the Train method
    // nn.test(test, featureSubset);

    return 0;
}


vector<vector<double>> getData(string& filename){
    vector<vector<double>> data;
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error: Could not open " << filename << endl;
        return data;
    }

    string line;
    while(getline(file, line)){
        vector<double> row;
        stringstream ss(line);
        double val;
        while(ss >> val){
            row.push_back(val);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

int numFeatures(vector<vector<double>> dataSet){
    return dataSet[0].size()-1;
}