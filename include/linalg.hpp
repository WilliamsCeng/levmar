/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Header file for Linear Algebra Functions
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/17/19
 */

#ifndef __LIN_ALG__
#define __LIN_ALG__
#include "matrix.h"
#include "vector.h"

#define TOL 1e-30

/* solve the equation Ax=b for a symmetric positive-definite matrix A,
   using the Cholesky decomposition A=LL^T.  The matrix L is passed in "l".
   Elements above the diagonal are ignored.
*/
//void solve_axb_cholesky(int n, double l[n][n], double x[n], double b[n]);
void solve_axb_cholesky(int n, matrix_2d<double> l, vector<double> x, vector<double> b);

/* This function takes a symmetric, positive-definite matrix "a" and returns
   its (lower-triangular) Cholesky factor in "l".  Elements above the
   diagonal are neither used nor modified.  The same array may be passed
   as both l and a, in which case the decomposition is performed in place.
*/
//int cholesky_decomp(int n, double l[n][n], double a[n][n]);
int cholesky_decomp(int n,  matrix_2d<double> l, matrix_2d<double> a);

#endif 