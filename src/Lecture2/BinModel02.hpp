//
//  BinModel.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <math.h>
#include <stdio.h>

#include <cmath>
#include <iostream>
#include <limits>

namespace lecture2 {

class BinModel {
public:
    BinModel(double S0, double U, double D, double R);
    double RiskNeutralProb();
    double S(int n, int i);
    double GetR();

private:
    double S0_;
    double U_;
    double D_;
    double R_;
    double T_;
};

}  // namespace lecture2
