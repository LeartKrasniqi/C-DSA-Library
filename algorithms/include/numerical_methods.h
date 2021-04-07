/* Header for Numerical Methods */
#ifndef _NUM_METHODS_H
#define _NUM_METHODS_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
*********************************
        Interface Methods
*********************************
*/

/* Polynomial Interpolation
    @param x   Array of points at which values are known
    @param fx  Array of values of the known points
    @param n   Number of known values
    @param z   Array of points at which values are to be interpolated
    @param pz  Array of interpolated values
    @param m   Number of values to be interpolated

    @return 0 if the interpolation is successful, -1 otherwise

    Notes:
      - Upon return , pz will contain the interpolated values
      - It is the responsibility of the caller to manage the storage associated with x, fx, z, and pz
      - Complexity: O(mn^2), where m is the number of values to be interpolated and n is the number of known values
*/
int poly_interp(const double *x, const double *fx, int n, double *z, double *pz, int m);


/* Least Squares Estimation
    @param x   Array of x-coordinates of points
    @param y   Array of y-coordinates of points
    @param n   Number of points
    @param b1  Coefficient
    @param b0  Coefficient

    @return None

    Notes:
      - Obtain b1 and b0 in y = b1*x + b0 so that y is a best-fit line through a set of points 
      - Upon return, b1 and b0 will contain the appropriate values
      - Complexity: O(n), where n is the number of points used in determining b1 and b0
*/
void least_squares(const double *x, const double *y, int n, double *b1, double *b0);


/* Solution of Equations
    @param f      Function whose root is to be found
    @param g      Derivative of function whose root is to be found
    @param x      Array of successive root approximations
    @param n      Maximum number of iterations to perform
    @param delta  Difference between successive root approximations at which to stop iterating

    @return 0 if a root is found, -1 otherwise 

    Notes:
      - Computes root of f using Newton's Method
      - x[0] should contain the initial iteration point (i.e., the initial approximation)
      - Upon return, x contains the successive approximations of the root and n contains the number values in x
      - It is the responsibility of the caller to manage the storage associated with x
      - Complexity: O(n), where n is the maximum number of iterations the caller wished to perform
*/
int root(double (*f)(double x), double (*g)(double x), double *x, int *n, double delta);

#endif
