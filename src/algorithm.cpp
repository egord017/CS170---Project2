#include "../header/algorithm.h"
#include <float.h>
using namespace std;

double evaluation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 100.0);
    return dis(gen);
}

vector<int> backwardElimination(int features) 
{
    cout << "Backward Elimination Search \n------------------------------\n";
    vector<int> selected_features; //vector to hold the current features
    double best_overall_accuracy = 0.0; //keep the highest accuracy
    vector<int> best_overall_features; //holds the best feature combo

    for (int i = 1; i <= features; i++) 
    {
        selected_features.push_back(i);
    }

    cout << "Using all features and \"random\" evaluation, I get an accuracy of: ";
    cout << fixed << setprecision(1) << evaluation() << "%\n\nBeginning search.\n\n";

    best_overall_accuracy = evaluation();
    best_overall_features = selected_features;

    for (int i = 0; i < features; i++)  
    {
        if (selected_features.empty()) 
        {
            break;
        }

        vector<int> current_best_features = selected_features;
        double current_best_accuracy = 0.0;

        for (auto feature = selected_features.begin(); feature != selected_features.end(); ++feature) 
        {
            vector<int> new_features = selected_features;
            new_features.erase(remove(new_features.begin(), new_features.end(), *feature), new_features.end()); //removes the current feature

            if (new_features.empty()) 
            {
                continue;
            }

            double accuracy = evaluation();
            cout << "\tUsing feature(s) {";
            for (auto iterate = new_features.begin(); iterate != new_features.end(); ++iterate) 
            {
                cout << *iterate;
                if (next(iterate) != new_features.end()) cout << ",";
            }
            cout << "} accuracy is " << fixed << setprecision(1) << accuracy << "%\n";

            if (accuracy > current_best_accuracy) //updates and tracks the current best feature
            {
                current_best_accuracy = accuracy;
                current_best_features = new_features;
            }
        }

        if (current_best_features != selected_features) //updates selected features if better subset found
        {
            selected_features = current_best_features;

            if (current_best_accuracy > best_overall_accuracy) //updates overall best feature set
            {
                best_overall_accuracy = current_best_accuracy;
                best_overall_features = selected_features;
            }

            cout << "\nFeature set {";
            for (auto iterate = selected_features.begin(); iterate != selected_features.end(); iterate++) 
            {
                cout << *iterate;
                if (next(iterate) != selected_features.end()) cout << ",";
            }
            cout << "} was best, accuracy is " << fixed << setprecision(1) << current_best_accuracy << "%";

            if (current_best_accuracy < best_overall_accuracy) //warning message for accuracy decreasing
            {
                cout << " \n(Warning, Accuracy has decreased!)\n\n";
            } else 
            {
                cout << "\n\n";
            }
        }
    }

    cout << "\nFinished search!! The best feature subset is {";
    for (auto iterate = best_overall_features.begin(); iterate != best_overall_features.end(); iterate++) 
    {
        cout << *iterate;
        if (next(iterate) != best_overall_features.end()) cout << ",";
    }
    cout << "}, which has an accuracy of " << fixed << setprecision(1) << best_overall_accuracy << "%\n\n";
    
    return best_overall_features;
}



vector<int> forwardSelection(int features)
{
    cout << "Forward Selection Search \n---------------------------\n";
    vector<int> selected_features; 
    double best_overall_accuracy = 0.0; //keeps track of highest accuracy %
    vector<int> best_overall_features; //keeps track of best feature set {}

    cout << "Using no features and \"random\" evaluation, I get an accuracy of: "; //basic output stuff for trace
    cout << fixed << setprecision(1) << evaluation() << "%\n\nBeginning search.\n\n";

    for (int i = 0; i < features; i++) //loops through the features the user Inputes
    {
        vector<int> current_best_features = selected_features;
        double current_best_accuracy = 0.0;
        int feature;

        for (feature = 1; feature <= features; feature++) //finds the best feature set
        {
            if(find(selected_features.begin(), selected_features.end(), feature) == selected_features.end()) //makes sure there arent duplicates in selected_features
            {
                vector<int> new_features = selected_features; //creates new feature set with the new feature. Ex.) {1} -> {1,3}
                new_features.push_back(feature);
                sort(new_features.begin(), new_features.end());
                
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
    return best_overall_features;
}



int Classifier::test(vector<double> testInstance, vector<int> featureSubset) {

    int classLabel = 0;
    double currentDist = 0;
    double nearestDist = DBL_MAX; //starting at max double val since we want smallest dist

   for (int i = 0; i < this->trainSet.size(); i++){
        double currentDist = calculateEuclidDistance(this->trainSet[i], testInstance, featureSubset); //get distance

        if (currentDist < nearestDist){
            nearestDist = currentDist;
            classLabel = this->trainSet[i][0];
            cout << "current shortest distance between TrainingSet ["<< i << "] with class label " << classLabel << "and the TestInstance is " << currentDist << endl; 
        }
   }

    cout << "\nFinal predicted class label for test instance is " << classLabel << endl;
    return classLabel;
}



// function "converts" values in each feature within the range of 0 and 1.
// this is done first by finding the min and max values in the feature set and applying the normalization formula.
vector<vector<double>> normalization(vector<vector<double>> dataSet) { 
   
    // for loop increments column.
    for (int i = 1; i <= 10; ++i) {

        double sum = 0;
        double summationStd = 0;

        //calculate sum and sum of squares
        for (int j = 0; j < dataSet.size(); j++){
            // sumSquare += pow(dataSet[j][i], 2);
            sum += dataSet[j][i];
        }
        //calc mean
        double mean = sum / dataSet.size();

        //calc std
        for(int j = 0; j < dataSet.size(); j++){
            double temp = dataSet[j][i] - mean;
            summationStd += pow(temp,2);
        }
    
        double temp = summationStd/dataSet.size();
        double std = sqrt(temp);

 
        //normalize
        for(int j = 0; j < dataSet.size(); j++){
            if(std != 0){
                dataSet[j][i] = (dataSet[j][i] - mean) / std;
            }
            else{
                dataSet[j][i] = 0;
            }
        }

    } 
    return dataSet;
}

double validator(vector<int> featureSubset, vector<vector<double>> dataSet){
    int correct = 0;

    for(int i = 0; i < dataSet.size(); i++){
        vector<double> testInstance = dataSet.at(i);
        int expectedClass = testInstance.at(0);

        //create a copy dataset with the testInstance row removed
        vector<vector<double>> leaveOneOutDataSet = dataSet;
        leaveOneOutDataSet.erase(leaveOneOutDataSet.begin()+i);

        //gets the predicted class of the leaveOneOut dataset
        Classifier leaveOneOut(leaveOneOutDataSet);
        int predictedClass = leaveOneOut.test(testInstance, featureSubset);

        if(predictedClass == expectedClass){
            correct++;
        }
    }

    return static_cast<double>(correct)/dataSet.size();
}

//takes the data points for the features the user selects and finds the euclidean distance
double calculateEuclidDistance(vector<double>& training, vector<double>& testing, vector<int>& features) 
{
    double sum = 0.0;
    double diff = 0.0;
    for(int i = 0; i < features.size(); i++) //iterates through each of the selected feature columns
    {
        diff = training[features[i]] - testing[features[i]]; // Ex.) x1 -x2
        sum += diff * diff; // Ex.) (x1 -x2)^2
    }
    return sqrt(sum); //gets the square root of the sum   
}