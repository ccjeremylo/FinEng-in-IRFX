//
//  BlackScholes.hpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>


double norm_cdf(const double& x);

double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T);

double call_price(const double& S, const double& K, const double& r, const double& v, const double& T);

double put_price(const double& S, const double& K, const double& r, const double& v, const double& T);
