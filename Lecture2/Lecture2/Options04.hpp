//
//  Options04.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>

#include "BinModel02.hpp"
#include "payoff.hpp"

void getOptionsInputData(int& N, double& K);

// pricing European option
double PriceByCRR(BinModel Model, int N, double K, double (*Payoff)(double z, double K));

//computing payoff
double CallPayoff(double z, double K);
double PutPayoff(double z, double K);

// analytical pricer
double PriceAnalytic(BinModel Model, int N, double K, double (*Payoff)(double z, double K));
