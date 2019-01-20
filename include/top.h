/* Copyright (C) Escape Technologies, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Contributors: Vineeth Yeevani <vineeth@escape-technologies.com>
 * Created on Dec 15, 2018
 * Description: Testbench for levmar newtons heating law
 * Version: 1.0
 * Changelog:
 *  + Created (Vineeth Yeevani) 1/19/19
 */

#ifndef __TOP__
#define __TOP__

#include "levmar.hpp"
int top(double *t_data, double *params, int n_params, int n_measurements, create_levmar_params);

#endif