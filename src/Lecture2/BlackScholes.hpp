//
//  BlackScholes.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <math.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

namespace lecture2 {

double norm_cdf(const double& x);

double d_j(const int& j, const double& S, const double& K, const double& r,
           const double& v, const double& T);

double call_price(const double& S, const double& K, const double& r,
                  const double& v, const double& T);

double put_price(const double& S, const double& K, const double& r,
                 const double& v, const double& T);

}  // namespace lecture2
