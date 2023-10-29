#pragma once

#include <math.h>

#include <iostream>
#include <vector>

#include "RNGenerator.hpp"

namespace lecture4 {

typedef std::vector<double> SamplePath;

// very basic design - should improve later using Joshi!
// ideally has a base class of "model"
class BSModel {
public:
    BSModel(double S0, double r, double sigma, rng::RNG generator);
    void GenerateSamplePath(double T, int m, SamplePath& S);
    double GetR();

protected:
    double S0_;
    double r_;
    double sigma_;
    rng::RNG generator_;
};

}  // namespace lecture4