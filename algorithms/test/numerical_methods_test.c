/* Testing the Numerical Methods */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "numerical_methods.h"

/* Model Function: f(x) = (x-3)(x+2)(x-1) */ 
double f(double x)
{
    return (x-3)*(x+2)*(x-1);
}

/* Derivative of Model Function: g(x) = d/dx[ x^3 - 7x^2 - 5x + 6 ] = 3x^2 - 14x - 5 */
double g(double x)
{
    return 3*pow(x,2) - (14*x) - 5;
}

int main()
{
    /*
    ****************************************
            Polynomial Interpolation
    ****************************************
    */
    
    /* The known points and values */
    double x[10], fx[10];
    for(int i = 0; i < 10; i++)
    {
        double x_val = (double)(i - 4);
        x[i] = x_val;
        fx[i] = f(x_val);
    }

    /* The desired points (along with their actual values, for verification) */
    double z[5], pz[5], fz[5];
    srand(time(NULL));
    for(int i = 0; i < 5; i++)
    {
        double z_val = (5) * ( (double)rand() / (double)RAND_MAX ) - 4;
        z[i] = z_val;
        fz[i] = f(z_val);
    }

    /* Perform the interpolation */
    poly_interp(x, fx, 10, z, pz, 5);

    /* Print out the results */
    printf("-------------------- POLYNOMIAL INTERPOLATION TEST START --------------------\n");
    printf("Interpolating values for f(x) = (x-3)(x+2)(x-1)\n");
    for(int i = 0; i < 5; i++)
        printf("Point %5.4f:  Interp = %5.4f  Actual = %5.4f  ==>  Diff = %5.4f\n", z[i], pz[i], fz[i], fabs(pz[i]-fz[i]));
    printf("-------------------- POLYNOMIAL INTERPOLATION TEST END --------------------\n\n");



    /*
    ****************************************
            Least Squares Estimation
    ****************************************
    */

    /* Construct points that kinda resemble y = 5x + 3 */
    double y[10];
    for(int i = 0; i < 10; i++)
    {
        double b1_noisy = 5 + ((0.02) * ( (double)rand() / (double)RAND_MAX ) - 0.01);
        double b0_noisy = 3 + ((0.025) * ( (double)rand() / (double)RAND_MAX ) + 0.025); 
        x[i] = (20) * ( (double)rand() / (double)RAND_MAX ) - 10;
        y[i] = b1_noisy*x[i] + b0_noisy;
        fx[i] = 5*x[i] + 3;
    }

    /* Perform the estimation */
    double b1, b0;
    least_squares(x, y, 10, &b1, &b0);

    /* Calculate the estimated values */
    double lsqe[10];
    for(int i = 0; i < 10; i++)
        lsqe[i] = b1*x[i] + b0;

    /* Print out the results */
    printf("-------------------- LEAST SQUARES ESTIMATION TEST START --------------------\n");
    printf("Estimating points resembling y = 5x + 3\n");
    for(int i = 0; i < 10; i++)
        printf("Point %5.4f:  Est = %5.4f  Actual = %5.4f  ==>  Diff = %5.4f\n", x[i], lsqe[i], fx[i], fabs(lsqe[i]-fx[i]));
    printf("-------------------- LEAST SQUARES ESTIMATION TEST END --------------------\n\n");

    
    

    /* 
    *************************************
            Solution of Equations
    *************************************
    */

    /* Set a number of iterations, the delta, and an initial estimate */
    int num_iter[3] = {20, 20, 20};
    double delta = 0.001;
    double *root_est[3];
    for(int i = 0; i < 3; i++)
        root_est[i] = malloc(num_iter[i] * sizeof(*root_est));
    double root_act[3] = {3.0, -2.0, 1.0};
    root_est[0][0] = 2.999;
    root_est[1][0] = -2.231;
    root_est[2][0] = 1.576;

    /* Find roots */
    for(int i = 0; i < 3; i++)
        root(f, g, root_est[i], &num_iter[i], delta);

    /* Print results */
    printf("-------------------- SOLUTION OF EQUATIONS TEST START --------------------\n");
    printf("Finding roots for f(x) = (x-3)(x+2)(x-1)\n");
    for(int i = 0; i < 3; i++)
    {
        double actual = root_act[i];
        double est = root_est[i][num_iter[i]-1];
        printf("Root %5.4f:  Estimate = %5.4f  ==>  Diff = %5.4f\n", actual, est, fabs(actual-est));
    }
    printf("-------------------- SOLUTION OF EQUATIONS TEST END --------------------\n\n");

    return 0;
}  

