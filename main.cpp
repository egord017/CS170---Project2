#include <iostream>
#include <random>

using namespace std;

double evaluation() {
    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<> dis(0.0, 100.0);

    return dis(gen);
}

int main() {
    
    for(int i = 0; i < 5; i++){
        double rand = evaluation();
        cout << rand << endl;
    }

    return 0;
}
