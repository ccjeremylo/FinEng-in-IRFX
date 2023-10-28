#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace rng {

class RNG {
public:
    RNG(int seed);
    virtual double Gauss();  // can't make pure..?
    int GetSeed();

protected:
    void incrementSeed();
    const double PI_;
    int seed_;
    int counter_;
};

class BoxMueller : public RNG {
public:
    BoxMueller(int seed);
    double Gauss();
};

}  // namespace rng