#include <iostream>
#include <math.h>

using namespace std;

double f(double mu, double sigma2, double x)
{
    //Use mu, sigma2 (sigma squared), and x to code the 1-dimensional Gaussian
    //Put your code here
    double e_pow_num = -1 * pow((x-mu),2);
    double e_pow_den = 2 * sigma2;
    double e_pow = e_pow_num / e_pow_den;
    double prob = (1 / (sqrt(sigma2) * sqrt(2*M_PI))) * pow(M_E,e_pow);
    return prob;
}

int main()
{
    cout << f(10.0, 4.0, 8.0) << endl;
    return 0;
}