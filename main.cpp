#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>//added so that we could use fixed and set precision

using namespace std;

double evaluation() {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(0.0, 100.0);

    return dis(gen);
}

void forwardSelection(int features)
{
    cout << "Forward Selection Search \n---------------------------\n";
    set<int> selected_features; //used set but could probably change it to vector if needed, uses begin() and end()
    double best_overall_accuracy = 0.0; //keeps track of highest accuracy %
    set<int> best_overall_features; //keeps track of best feature set {}

    cout << "Using no features and \"random\" evaluation, I get an accuracy of: "; //basic output stuff for trace
    cout << fixed << setprecision(1) << evaluation() << "%\n\nBeginning search.\n\n";

    for (int i = 0; i < features; i++) //loops through the features the user Inputes
    {
        set<int> current_best_features = selected_features;
        double current_best_accuracy = 0.0;
        int feature;

        for (feature = 1; feature <= features; feature++) //finds the best feature set
        {
            if (selected_features.find(feature) == selected_features.end()) //makes sure there arent duplicates in selected_features
            {
                set<int> new_features = selected_features; //creates new feature set with the new feature. Ex.) {1} -> {1,3}
                new_features.insert(feature);
                
                double accuracy = evaluation(); //doing the random accuracy
                cout << "\t Using feature(s) {";
                for (auto iterate = new_features.begin(); iterate != new_features.end(); iterate++) //auto automatically finds the type
                {
                    cout << *iterate; //prints the set ex.) {1}, {2}
                    if (next(iterate) != new_features.end()) cout << ","; //checks to see if there are more elements to print
                }
                cout << "} accuracy is " << fixed << setprecision(1) << accuracy << "%\n";

                if (accuracy > current_best_accuracy) //updates the current best accuracy
                {
                    current_best_accuracy = accuracy;
                    current_best_features = new_features;
                }
            }
        }

        selected_features = current_best_features; //keeps track of the iterated best feature set

        if (current_best_accuracy > best_overall_accuracy) //updates the overall highest accuracy
        {
            best_overall_accuracy = current_best_accuracy;
            best_overall_features = selected_features;
        }

        cout << "\nFeature set {";
        for (auto iterate = selected_features.begin(); iterate != selected_features.end(); iterate++) 
        {
            cout << *iterate; //outputs the current set 
            if (next(iterate) != selected_features.end()) cout << ",";
        }

        cout << "} was best, accuracy is " ;
        cout << fixed << setprecision(1) << current_best_accuracy << "%"; //outputs the above sets' accuracy percentage

        if(current_best_accuracy < best_overall_accuracy) //conditional print statements for if there is an accuracy decrease. mostly just to match the trace formatting
        {
            cout << " \n(Warning, Accuracy has decreased!)\n\n";
        } 
        else 
        {
            cout << "\n\n";
        }
        
    }
    
    cout << "\nFinished search!! The best feature subset is {";
    for (auto iterate = best_overall_features.begin(); iterate != best_overall_features.end(); iterate++) //prints the best feature set
    { 
        cout << *iterate;
        if (next(iterate) != best_overall_features.end()) cout << ",";
    }
    cout << "}, which has an accuracy of " << fixed << setprecision(1) << best_overall_accuracy << "%\n\n";
}

//Added lines 103-106,117-119,126-132
void backwardElimination(int features)
{
    cout << "Backward Elimination Search \n------------------------------\n";
    set<int> selected_features; // used set but could probably change it to vector if needed, uses begin() and end()
    double best_overall_accuracy = 0.0; // keeps track of highest accuracy %
    set<int> best_overall_features; // keeps track of best feature set {}

    for (int i = 1; i <= features; i++) // Initializes the selected_features set with all features, opposite of forward
    {
        selected_features.insert(i);
    }

    // Evaluate the accuracy with all features
    cout << "Using all features and \"random\" evaluation, I get an accuracy of: ";
    cout << fixed << setprecision(1) << evaluation() << "%\n\nBeginning search.\n\n";

    best_overall_accuracy = evaluation();
    best_overall_features = selected_features;

    for (int i = 0; i < features; i++) // loops through the features
    {
        if (selected_features.empty()) {
            break; // Exit the loop if there are no more features e.g. {}
        }

        set<int> current_best_features = selected_features;
        double current_best_accuracy = 0.0;

        for (auto feature = selected_features.begin(); feature != selected_features.end(); ++feature) // finds the best feature set
        {
            set<int> new_features = selected_features; //creates new feature set that doesnt have the current feature
            new_features.erase(*feature);

            if (new_features.empty()) // Skip the empty set
            {
                continue; 
            }
                
            double accuracy = evaluation(); // doing the random accuracy
            cout << "\t Using feature(s) {";
            for (auto iterate = new_features.begin(); iterate != new_features.end(); iterate++) // auto automatically finds the type
            {
                cout << *iterate; // prints the set ex.) {1}, {2}
                if (next(iterate) != new_features.end()) cout << ","; // checks to see if there are more elements to print
            }
            cout << "} accuracy is " << fixed << setprecision(1) << accuracy << "%\n";

            if (accuracy > current_best_accuracy) // updates the current best accuracy
            {
                current_best_accuracy = accuracy;
                current_best_features = new_features;
            }
        }

        // Update only if current_best_features is different from selected_features. Used to get rid of the duplicate output emssage
        if (current_best_features != selected_features) 
        {
            selected_features = current_best_features; // keeps track of the iterated best feature set

            if (current_best_accuracy > best_overall_accuracy) // updates the overall highest accuracy
            {
                best_overall_accuracy = current_best_accuracy;
                best_overall_features = selected_features;
            }

            cout << "\nFeature set {";
            for (auto iterate = selected_features.begin(); iterate != selected_features.end(); iterate++) 
            {
                cout << *iterate; // outputs the current set 
                if (next(iterate) != selected_features.end()) cout << ",";
            }

            cout << "} was best, accuracy is ";
            cout << fixed << setprecision(1) << current_best_accuracy << "%"; // outputs the above sets' accuracy percentage

            if(current_best_accuracy < best_overall_accuracy) // conditional print statements for if there is an accuracy decrease. mostly just to match the trace formatting
            {
                cout << " \n(Warning, Accuracy has decreased!)\n\n";
            } 
            else 
            {
                cout << "\n\n";
            }
        }
    }
    
    cout << "\nFinished search!! The best feature subset is {";
    for (auto iterate = best_overall_features.begin(); iterate != best_overall_features.end(); iterate++) // prints the best feature set
    { 
        cout << *iterate;
        if (next(iterate) != best_overall_features.end()) cout << ",";
    }
    cout << "}, which has an accuracy of " << fixed << setprecision(1) << best_overall_accuracy << "%\n\n";
}




int main() {
    
    std::vector<double> accuracy;

    //system("cls");
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
        

    } while(userChoice != 1 && userChoice !=2 && userChoice != 3);
    cout << " \n\n\n";
    //system("cls");

    if(userChoice == 1){
        forwardSelection(userInput);
    }
    else if(userChoice == 2){
        backwardElimination(userInput);
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
