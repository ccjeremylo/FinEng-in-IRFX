#pragma once

#include <iostream>

#include "../Lecture4/RNGenerator.hpp"
#include "Matrix.hpp"

namespace lecture5 {

typedef std::vector<matrix::Vector> SamplePath;  // same as matrix::Matrix

class BSModel {
public:
    BSModel(matrix::Vector S0, double r, matrix::Matrix C,
            rng::RNG& generator);
    void GenerateSamplePath(double T, int m, SamplePath& S);
    double GetR();
    int GetDim();
    matrix::Vector GetS0();
    matrix::Matrix GetVolMatrix();

protected:
    matrix::Vector S0_, sigma_;
    matrix::Matrix C_;
    double r_;
    rng::RNG& generator_;
};

}  // namespace lecture5
