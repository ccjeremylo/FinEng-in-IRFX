#pragma once

#include <cmath>
#include <iostream>

#include "BSModel01.hpp"

namespace lecture4 {

// should support vanilla options as well
class PathDepOption {
public:
    PathDepOption(double T, int m, bool isCall);
    double PriceByMC(lecture4::BSModel &Model, long N);
    double PriceByControlVariateMC(lecture4::BSModel &Model, long N,
                                   PathDepOption &CVOption);
    virtual double PriceByFormula(lecture4::BSModel Model) {
        return -100;
    };
    virtual double Payoff(lecture4::SamplePath &S) { return -100; };
    double GetPricingError() { return PricingError_; };
    double GetPrice() { return Price_; };

protected:
    bool isCall_;
    double T_;
    int m_;
    double Price_;
    double PricingError_;
};

// Asian
class ArithAsian : public PathDepOption {
public:
    ArithAsian(double T, int m, double K, bool isCall);
    double Payoff(lecture4::SamplePath &S);

protected:
    double K_;
};

// need an analytical pricer!
class GeomAsian : public PathDepOption {
public:
    GeomAsian(double T, int m, double K, bool isCall);
    double Payoff(lecture4::SamplePath &S);
    double PriceByFormula(lecture4::BSModel Model);

protected:
    double K_;
};

// Vanilla
class Vanilla : public PathDepOption {
public:
    Vanilla(double T, int m, double K, bool isCall);
    double Payoff(lecture4::SamplePath &S);
    double PriceByFormula(lecture4::BSModel Model);

protected:
    double K_;
};

// Barriers
class DoubleBarrierKO : public PathDepOption {
public:
    DoubleBarrierKO(double T, int m, double K, double Bup, double Bdown,
                    bool isCall);
    double PriceByVanillaCVMC(lecture4::BSModel &Model, long N,
                              Vanilla &CVOption);
    double Payoff(lecture4::SamplePath &S);

protected:
    double K_;
    double Bup_;
    double Bdown_;
};

class DoubleBarrierKI : public PathDepOption {
public:
    DoubleBarrierKI(double T, int m, double K, double Bup, double Bdown,
                    bool isCall);
    double PriceByVanillaCVMC(lecture4::BSModel &Model, long N,
                              Vanilla &CVOption);
    double Payoff(lecture4::SamplePath &S);

protected:
    double K_;
    double Bup_;
    double Bdown_;
};

}  // namespace lecture4