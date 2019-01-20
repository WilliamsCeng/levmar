/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Testbench for levmar newtons heating law
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/17/19
 *  + Renamed and refactoring to make
 *    this file be the top function entry for hls 
 *    (Vineeth Yeevani) 1/19/19
 */

#include "top.h"

class newton_heating_model : public levmar_solver
{
  public:
    // If initialized for fixed algorithm
    newton_heating_model() : levmar_solver()
    {
        //create_levmar_static_var(N_PARAMS);
    }

    newton_heating_model(int n_param, double *g_data,
                         double *d_data, double *delta_data,
                         double *newpar_data, double *h_data, 
                         double *ch_data)
        : levmar_solver(n_param, g_data, d_data,
                        delta_data, newpar_data,
                        h_data, ch_data)
    {
    }

    /* @brief   Function, describes Newton law of heating/cooling
    *
    * @usage   par[0] - temperature of heater,
    *          par[1] - initial temperature of water,
    *          par[2] - heat transmission coefficient
    *
    * @par     input of Newton Law:
    * @x       samplenumber
    * @fdata   additional data, not used
    *
    * @return  temperature at the time x
    */
    double func(vector<double> par, int x) override
    {
        return par[0] + (par[1] - par[0]) * exp(-par[2] * x);
    }

    /*
    * @brief   Gradient function for Newton law of heating
    */
    void grad(vector<double> g, vector<double> par, int x) override
    {
        g[0] = 1.0 - exp(-par[2] * x);
        g[1] = exp(-par[2] * x);
        g[2] = -x * (par[1] - par[0]) * exp(-par[2] * x);
    }
};

/*
 * @brief  Function for prediction of time, when target temperature will be reached
 * 
 * @par    Parameters from Newton equation
 * @temp   Target temperature
 * @return Number of sample
 */

int temp_to_time(vector<double> par, double temp)
{
    return -(1 / par[2]) * log((temp - par[0]) / (par[1] - par[0]));
}

int top(double *t_data, double *params, int n_params, int n_measurements, create_levmar_params)
{
    vector<double> par = vector<double>(params, n_params);
    vector<double> data = vector<double>(t_data, n_measurements);
    int n_iterations;
    vector<double> garbage;
    garbage.clear();
    newton_heating_model model = newton_heating_model(n_params, g, d, delta, newpar, h, ch);
    model.levmarq(n_params, par, n_measurements, data, false, garbage);

    printf("**************** End of calculation ***********************\n");
    printf("N iterations: %d\n", model.get_iter());
    printf("T_heater: %f, T_0: %f, k: %f\n",
           par[0], par[1], par[2]);
    printf("**************** Interpolation test ***********************\n");
    printf("Search for temp 70 degrees\n");
    printf("Result: %d sample\n", temp_to_time(par, 50.0));
    return 0;
}