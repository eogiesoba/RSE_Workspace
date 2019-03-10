#include <iostream>
#include <math.h>
#include <tuple>
#include "Core" // Eigen Library
#include "LU"   // Eigen Library

using namespace std;
using namespace Eigen;

float measurements[3] = { 1, 2, 3 }; //Measurement array

tuple<MatrixXf, MatrixXf> kalman_filter(MatrixXf x, MatrixXf P, MatrixXf u, MatrixXf F, MatrixXf H, MatrixXf R, MatrixXf I)
{
    for (int n = 0; n < sizeof(measurements) / sizeof(measurements[0]); n++) {

        // Measurement Update
        MatrixXf Z(1, 1);  // Define a 1 row by 1 col matrix Z
        Z << measurements[n];

        MatrixXf y(1, 1);
        y << Z - (H * x);

        MatrixXf S(1, 1); 
        S << H * P * H.transpose() + R; // Calculate S for measurement update

        MatrixXf K(2, 1); // Define a 2 row by 1 col matrix K
        K << P * H.transpose() * S.inverse(); // Calculate of K --> Kalman Gain for measurement update

        // Measurement Update based of robot sensor
        x << x + (K * y); // x = x' + Ky; where x is the posterior state
        P << (I - (K * H)) * P; // P = (I - KH)P'; where P is the posterior covariance

        // State Prediction, based of motion of robots
        x << (F * x) + u; // x' = (F * x) + u; u is the noise with assumption of zero noise
        P << F * P * F.transpose(); // P' = (F * P * Ft) + Q ; Q is the noise with assumption of zero noise
    }

    return make_tuple(x, P); //This will return the last prediction values for state and covariance.
}

int main()
{

    MatrixXf x(2, 1);// Initial state (location and velocity) 
    x << 0,
    	 0; 
    MatrixXf P(2, 2);//Initial Uncertainty
    P << 100, 0,  //100 for variance in the location and velocity, and 0 for correlation terms.
    	 0, 100; 
    MatrixXf u(2, 1);// External Motion
    u << 0,
    	 0; 
    MatrixXf F(2, 2);//Next State Function
    F << 1, 1,
    	 0, 1; 
    MatrixXf H(1, 2);//Measurement Function
    H << 1,
    	 0; 
    MatrixXf R(1, 1); //Measurement Uncertainty
    R << 1;
    MatrixXf I(2, 2);// Identity Matrix
    I << 1, 0,
    	 0, 1; 

    tie(x, P) = kalman_filter(x, P, u, F, H, R, I);
    cout << "x= " << x << endl; //last prediction of x value after 3 iterations of the multidimensional KF
    cout << "P= " << P << endl; //last prediction of P value after 3 iterations of the multidimensional KF

    return 0;
}