/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Impl file for Levenberg Marquadt algorithm
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/17/19
 */

#include "levmar.hpp"

void levmar_solver::init()
{
    verbose = 0;
    max_it = 10000;
    init_lambda = 0.0001;
    up_factor = 10;
    down_factor = 10;
    target_derr = 1e-12;
}

// Default constructor
levmar_solver::levmar_solver()
{
    init();

    // Demonstrating how solver data is used keep in
    // mind static data is not destroyed when a function ends
    // so all data will be persisted forever
    // create_matrix_2d_data(h, 10, 10, double);
    // create_matrix_2d_data(ch, 10, 10, double);
}

levmar_solver::levmar_solver(vector<double> input_g, vector<double> input_d, vector<double> input_delta,
                             vector<double> input_newpar, matrix_2d<double> input_h, matrix_2d<double> input_ch)
{
    g = input_g;
    d = input_d;
    delta = input_delta;
    newpar = input_newpar;
    h = input_h;
    ch = input_ch;
    init();
}

levmar_solver::levmar_solver(int n_param, double *g_data, double *d_data, double *delta_data,
                             double *newpar_data, double *h_data, double *ch_data)
{
    g = vector<double>(g_data, n_param);
    d = vector<double>(d_data, n_param);
    delta = vector<double>(delta_data, n_param);
    newpar = vector<double>(newpar_data, n_param);
    h = matrix_2d<double>(h_data, n_param, n_param);
    ch = matrix_2d<double>(ch_data, n_param, n_param);

    init();

    g.clear();
    d.clear();
    delta.clear();
    newpar.clear();
    h.clear();
    ch.clear();
}

// Reset function
void levmar_solver::reset()
{
    verbose = 0;
    max_it = 10000;
    init_lambda = 0.0001;
    up_factor = 10;
    down_factor = 10;
    target_derr = 1e-12;
}

int levmar_solver::levmarq(int npar, vector<double> par, int ny, vector<double> y,
                           bool weighted, vector<double> dysq)
{
    int x, i, j, it, nit, ill;
    double lambda, up, down, mult, weight, err, newerr, derr, target_derr;
    // double h[npar][npar], ch[npar][npar];
    // double g[npar], d[npar], delta[npar], newpar[npar];
    // vector<double> g, d, delta, newpar;
    // matrix_2d<double> h, ch;
    nit = max_it;
    lambda = init_lambda;
    up = up_factor;
    down = 1 / down_factor;
    target_derr = target_derr;
    weight = 1;
    derr = newerr = 0; /* to avoid compiler warnings */
    /* calculate the initial error ("chi-squared") */
    err = error_func(par, ny, y, weighted, dysq);

    /* main iteration */
    for (it = 0; it < nit; it++)
    {
        /* calculate the approximation to the Hessian and the "derivative" d */
        for (i = 0; i < npar; i++)
        {
            d[i] = 0;
            for (j = 0; j <= i; j++)
                h[i][j] = 0;
        }
        for (x = 0; x < ny; x++)
        {
            if (weighted)
            {
                weight = 1 / dysq[x]; /* for weighted least-squares */
            }
            grad(g, par, x);
            for (i = 0; i < npar; i++)
            {
                d[i] += (y[x] - func(par, x)) * g[i] * weight;
                for (j = 0; j <= i; j++)
                    h[i][j] += g[i] * g[j] * weight;
            }
        }

        /*  make a step "delta."  If the step is rejected, increase
        lambda and try again */
        mult = 1 + lambda;
        ill = 1; /* ill-conditioned? */
        while (ill && (it < nit))
        {
            for (i = 0; i < npar; i++)
                h[i][i] = h[i][i] * mult;

            ill = cholesky_decomp(npar, ch, h);
            // std::cout << "start mat h " << h << std::endl;
            // std::cout << "cholesky " << ch << std::endl;
            if (!ill)
            {
                solve_axb_cholesky(npar, ch, delta, d);
                for (i = 0; i < npar; i++)
                    newpar[i] = par[i] + delta[i];
                newerr = error_func(newpar, ny, y, weighted, dysq);
                derr = newerr - err;
                ill = (derr > 0);
            }
            if (verbose)
                printf("it = %4d,   lambda = %10g,   err = %10g,   "
                       "derr = %10g\n",
                       it, lambda, err, derr);
            if (ill)
            {
                mult = (1 + lambda * up) / (1 + lambda);
                lambda *= up;
                it++;
            }
        }
        for (i = 0; i < npar; i++)
            par[i] = newpar[i];
        err = newerr;
        lambda *= down;

        if ((!ill) && (-derr < target_derr))
        {
            break;
        }
    }

    final_it = it;
    final_err = err;
    final_derr = derr;

    return (it == nit);
}

/* calculate the error function (chi-squared) */
double levmar_solver::error_func(vector<double> par,
                                 int ny, vector<double> y,
                                 bool weighted,
                                 vector<double> dysq)
{
    int x;
    double res, e = 0;

    for (x = 0; x < ny; x++)
    {
        res = func(par, x) - y[x];
        if (weighted)
        {
            /* weighted least-squares */
            e += res * res / dysq[x];
        }
        else
        {
            e += res * res;
        }
    }
    return e;
}

int levmar_solver::get_iter()
{
    return final_it;
}