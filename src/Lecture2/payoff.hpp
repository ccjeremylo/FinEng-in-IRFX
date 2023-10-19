//
//  payoff.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>

namespace lecture2 {

//computing payoff
double CallPayoff(double z, double K);
double PutPayoff(double z, double K);

}
