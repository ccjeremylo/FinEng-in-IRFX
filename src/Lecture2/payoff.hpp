//
//  payoff.hpp
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

// computing payoff
double CallPayoff(double z, double K);
double PutPayoff(double z, double K);

double DigitalCallPayoff(double z, double K);
double DigitalPutPayoff(double z, double K);

}  // namespace lecture2
