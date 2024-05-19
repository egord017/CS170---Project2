#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

double evaluation() {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(0.0, 100.0);

    return dis(gen);
}

void forwardSelection(int features)
{

}
int main() {
    
    std::vector<double> accuracy;

    system("cls");
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
        cout << "please choose a number between 1 and 3: ";

    } while(userChoice != 1 && userChoice !=2 && userChoice != 3);
    cout << " \n";

    if(userChoice == 1){
        forwardSelection(userInput);
    }
    else if(userChoice == 2){

    }
    else{

    }

    // for(int i = 0; i < 5; i++){
    //     double rand = evaluation();
    //     accuracy.push_back(rand);
    //     cout << rand << endl;
    // }

    return 0;
}
