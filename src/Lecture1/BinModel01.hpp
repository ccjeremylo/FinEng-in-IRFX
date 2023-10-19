//
//  pricing_functions.hpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//

#pragma once

#include <stdio.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

namespace lecture1 {

double NewtonSymb(int N, int i);

void getInputData(double &S0, double &U, double &D, double &R);

double riskNeutralProb(const double &U, const double &D, const double &R);

double S(const double &S0, const double &U, const double &D, const int& n, const int& i);
}