//
//  Options01.hpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//

#pragma once
#include <fstream>
#include "BinModel01.hpp"

namespace lecture1 {

void getOptionsInputData(int& N, double& K);

// pricing European option
double PriceByCRR(double S0, double U, double D, double R, int N, double K,
                  double (*Payoff)(double z, double K));

// computing payoff
double CallPayoff(double z, double K);
double PutPayoff(double z, double K);

// analytical pricer
double PriceAnalytic(double S0, double U, double D, double R, int N, double K,
                     double (*Payoff)(double z, double K));

}  // namespace lecture1