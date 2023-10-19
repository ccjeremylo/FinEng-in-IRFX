//
//  BinModel.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
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

}
