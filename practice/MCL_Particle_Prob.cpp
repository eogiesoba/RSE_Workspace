#include <iostream>

using namespace std;

double w[] = { 0.6, 1.2, 2.4, 0.6, 1.2 };//You can also change this to a vector
double W = 0.0; //Total weight

//TODO: Define a  ComputeProb function and compute the Probabilities
void ComputeProb(double weight[], int size){
    for (int i=0; i < size; i++){
        W += weight[i];
    }
    for (int j=0; j < size; j++){
        cout << "P"<<j+1<<"="<< weight[j]/W << endl;
    }
}

int main()
{
    //Print Probabilites each on a single line:
    //P1=Value
    //:
    //P5=Value
    ComputeProb(w, sizeof(w) / sizeof(w[0]));
    
    return 0;
}
