/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Impl file for Linear Algebra Functions
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/18/19
 */

#include "linalg.hpp"

void solve_axb_cholesky(int n, matrix_2d<double> l, vector<double> x, vector<double> b)
{
    int i, j;
    double sum;

    /* solve L*y = b for y (where x[] is used to store y) */

    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < i; j++)
            sum += l[i][j] * x[j];
        x[i] = (b[i] - sum) / l[i][i];
    }

    /* solve L^T*x = y for x (where x[] is used to store both y and x) */

    for (i = n - 1; i >= 0; i--)
    {
        sum = 0;
        for (j = i + 1; j < n; j++)
            sum += l[j][i] * x[j];
        x[i] = (x[i] - sum) / l[i][i];
    }
}

int cholesky_decomp(int n, matrix_2d<double> l, matrix_2d<double> a)
{
    int i, j, k;
    double sum;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            sum = 0;
            for (k = 0; k < j; k++)
                sum += l[i][k] * l[j][k];
            l[i][j] = (a[i][j] - sum) / l[j][j];
        }

        sum = 0;
        for (k = 0; k < i; k++)
            sum += l[i][k] * l[i][k];
        sum = a[i][i] - sum;
        if (sum < TOL)
            return 1; /* not positive-definite */
        l[i][i] = sqrt(sum);
    }
    return 0;
}