/* Implementation of Numerical Methods */
#include "numerical_methods.h"

/* Polynomial Interpolation */
int poly_interp(const double *x, const double *fx, int n, double *z, double *pz, int m)
{
    /* Perform interpolation using a divided-difference table */
    double *table = malloc(n * sizeof(*table));
    if(table == NULL)
        return -1;

    /* Allocate memory for the coefficients in the table */
    double *coeff = malloc(n * sizeof(*coeff));
    if(coeff == NULL)
    {
        free(table);
        return -1;
    }

    /* Initialize the coefficients */
    memcpy(table, fx, n * sizeof(double));
    coeff[0] = table[0];

    /* Compute divide-differences along the "diagonal" of the table */
    for(int i = 1; i < n; i++)
    {
        /* f[xi,xj] = (f(xi) - f(xj)) / (xi - xj) */
        for(int j = 0; j < n - i; j++)
            table[j] = (table[j+1] - table[j]) / (x[i+j] - x[j]);
        
        coeff[i] = table[0];
    }

    /* Find pz using the Newton formula: p(z) = f[x0] + f[x0,x1](z-x0) + ... + f[x0,...,xn](z-x0)...(z-x_{n-1}) */
    for(int i = 0; i < m; i++)
    {
        /* f[x0] */
        pz[i] = coeff[0];

        /* f[x0,x1](z-x0) + ... + f[x0,...,xn](z-x0)...(z-x_{n-1}) */ 
        for(int j = 1; j < n; j++)
        {
            /* f[x0,...,xj] */
            double term = coeff[j];
             
            /* f[x0,...,xj](z-x0)...(z-xj) */
            for(int k = 0; k < j; k++)
                term *= (z[i] - x[k]);

            /* Add it all up */
            pz[i] += term;
        } 
    }

    /* Cleanup */
    free(table);
    free(coeff);

    /* If we get here, pz contains the interpolation polynomial */
    return 0;
}


/* Least Squares Estimation */
void least_squares(const double *x, const double *y, int n, double *b1, double *b0)
{
    /* Formulas for b1 and b0:
        
              n∑xy - ∑x∑y               ∑y - b1∑x
        b1 = --------------        b0 = ---------         
             n∑x^2 - (∑x)^2                 n

    */


    /* Initialize the sums */
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_x2 = 0.0;
    double sum_xy = 0.0;

    /* Compute the sums */
    for(int i = 0; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_x2 += pow(x[i], 2.0);
        sum_xy += (x[i] * y[i]);
    }

    /* Calculate the coefficients */
    double b1_num = (((double)n)*sum_xy) - (sum_x*sum_y);
    double b1_den = (((double)n)*sum_x2) - pow(sum_x, 2.0);
    *b1 = b1_num / b1_den;

    double b0_num = sum_y - ((*b1)*sum_x);
    double b0_den = (double)n;
    *b0 = b0_num / b0_den;    
}


/* Solution of Equations */
int root(double (*f)(double x), double (*g)(double x), double *x, int *n, double delta)
{
    /* Use Newton's Method to find a root of f:
        1. Select an initial point, x0
        2. Calculate:
                          f(xi)
                x_{i+1} = -----
                          g(xi)

        3. Check if abs(x_{i+1} - xi) falls within delta
    
    */

    int close_enough = 0;
    int iter = 0;

    /* Perform Newton's Method until we are close enough or reached max number of iterations */
    while(!close_enough && (iter + 1 < *n))
    {
        /* Calculate the next iteration of x */
        x[iter+1] = x[iter] - (f(x[iter]) / g(x[iter]));

        /* Check if difference is close enough to delta */
        if(fabs(x[iter+1] - x[iter]) < delta)
            close_enough = 1;

        /* Move onto the next iteration */
        iter++;
    }

    /* At least one value exists in x (the initial estimate) */
    if(iter == 0)
        *n = 1;
    else
        *n = iter + 1;

    /* Return whether a root was found or max iterations were reached */
    if(close_enough)
        return 0;
    else
        return -1;

}

