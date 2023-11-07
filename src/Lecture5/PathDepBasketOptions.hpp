#pragma once

#include <cmath>
#include <iostream>

#include "BSModel02.hpp"

namespace lecture5 {

// ideally should just re-use lecture 4 code...
class PathDepBasketOption {
public:
    PathDepBasketOption(double T, int m, bool isCall);
    double PriceByMC(lecture5::BSModel &Model, long N);
    virtual double Payoff(lecture5::SamplePath &S) = 0;  // pure vitual
    double GetPricingError() { return PricingError_; };
    double GetPrice() { return Price_; };

protected:
    bool isCall_;
    double T_;
    int m_;
    double Price_;
    double PricingError_;
};

// Basket
class VanillaBasket : public PathDepBasketOption {
public:
    VanillaBasket(double T, int m, double K, bool isCall);
    double Payoff(lecture5::SamplePath &S);

protected:
    double K_;
};

}  // namespace lecture5