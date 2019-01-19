/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Header file for Levenberg Marquadt algorithm
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/17/19
 */

#ifndef __LEV_MAR__
#define __LEV_MAR__

#include "linalg.hpp"

#define create_levmar_static_var(size)             \
  {                                                \
    create_vec_data(g, size, double);              \
    create_vec_data(d, size, double);              \
    create_vec_data(delta, size, double);          \
    create_vec_data(newpar, size, double);         \
    create_matrix_2d_data(h, size, size, double);  \
    create_matrix_2d_data(ch, size, size, double); \
  }

class levmar_solver
{
protected:
  int verbose;
  int max_it;
  double init_lambda;
  double up_factor;
  double down_factor;
  double target_derr;
  int final_it;
  double final_err;
  double final_derr;

  // Need to init these vectors in child classes
  vector<double> g, d, delta, newpar;
  matrix_2d<double> h, ch;

public:
  // Constructor
  levmar_solver();

  // Reset state
  void reset();

  // Virtual functions for derived classes to fit
  virtual double func(vector<double>, int) = 0;
  virtual void grad(vector<double>, vector<double>, int) {};

  /* perform least-squares minimization using the Levenberg-Marquardt
    algorithm.  The arguments are as follows:
    npar    number of parameters
    par     array of parameters to be varied
    ny      number of measurements to be fit
    y       array of measurements
    dysq    array of error in measurements, squared
            (set dysq=NULL for unweighted least-squares)
    func    function to be fit
    grad    gradient of "func" with respect to the input parameters
    fdata   pointer to any additional data required by the function
    lmstat  pointer to the "status" structure, where minimization parameters
            are set and the final status is returned.
    Before calling levmarq, several of the parameters in lmstat must be set.
    For default values, call levmarq_init(lmstat).
    
    int levmarq(int npar, double *par, int ny, double *y, double *dysq,
                double (*func)(double *, int, void *),
                void (*grad)(double *, double *, int, void *),
                void *fdata);
    */

  int levmarq(int npar, vector<double> par, int ny, vector<double> y,
              bool weighted, vector<double> dysq);

  int get_iter();

  /*double error_func(double *par, int ny, double *y, double *dysq,
                      double (*func)(double *, int, void *), void *fdata);*/
  double error_func(vector<double> par, int ny, vector<double> y, bool weighted, vector<double> dysq);
};

#endif