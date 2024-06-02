
#include "../header/algorithm.h"
#include <set>
#include <fstream>
#include <sstream>

vector<vector<double>> getData(string& filename);

int main() {
    
    std::vector<double> accuracy;

    string file = "./txt/small-test-dataset.txt";
    vector<vector<double>> dataSet = getData(file);

    int userInput; 
    cout << "Welcome to the Feature Selection Algorithm \n";
    cout << "Please enter total number of features: ";
    cin >> userInput;
    cout << " \n";


    int userChoice;
    cout << "Type the number of the algorithm you want to run(1-3): \n";
    cout << "1. Forward Selection \n";
    cout << "2. Backward Elimination \n";
    cout << "3. Special Alogrithm \n";
    do{
        cin >> userChoice;
        if(cin.fail()){
            
            cin.clear();
            cin.ignore(10000 , '\n');
            
        }
        

    } while(userChoice != 1 && userChoice !=2 && userChoice != 3 && userChoice != 4);
    cout << " \n\n\n";

    if(userChoice == 1){
        forwardSelection(userInput);
    }
    else if(userChoice == 2){
        backwardElimination(userInput);
    }
    else if (userChoice == 3) {
        nearestNeighbor(dataSet);
    } else if (userChoice == 4) {
        normalization(dataSet);
    } else { 

    }

    // for(int i = 0; i < 5; i++){
    //     double rand = evaluation();
    //     accuracy.push_back(rand);
    //     cout << rand << endl;
    // }

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