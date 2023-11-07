#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "../Lecture5/Matrix.hpp"

namespace rng {

class RNG {
public:
    RNG(int seed);
    virtual double Gauss();  // can't make pure..?
    virtual matrix::Vector GaussVector(int d);
    int GetSeed();

protected:
    void incrementSeed();
    const double PI_;
    int seed_;
    int counter_;
};

class BoxMuller : public RNG {
public:
    BoxMuller(int seed);
    double Gauss();
    matrix::Vector GaussVector(int d);
};

}  // namespace rng