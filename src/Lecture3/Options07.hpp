
#pragma once

#include <math.h>
#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../Lecture2/BinModel02.hpp"

namespace lecture3 {

// don't like this design, options should have no knowledge about the model
class EurOption {
public:
    EurOption(int N);
    virtual double Payoff(double z) = 0;
    double PriceByCRR(lecture2::BinModel Model);

protected:
    int N_;
};

class AmOption {
public:
    AmOption(int N);
    virtual double Payoff(double z) = 0;
    double PriceBySnell(lecture2::BinModel Model);

protected:
    int N_;
};

// call and put - multiple inheriance!

class Call : public EurOption, public AmOption {
public:
    Call(double K, int N);
    double Payoff(double z);

protected:
    int K_;
};

class Put : public EurOption, public AmOption {
public:
    Put(double K, int N);
    double Payoff(double z);

protected:
    int K_;
};

}  // namespace lecture3
