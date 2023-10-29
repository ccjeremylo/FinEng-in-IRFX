#pragma once

#include "BSModel01.hpp"

namespace lecture4 {

// should support vanilla options as well
class PathDepOption {
public:
    PathDepOption(double T, int m, bool isCall);
    double PriceByMC(lecture4::BSModel Model, long N);

    virtual double Payoff(lecture4::SamplePath& S) = 0;

protected:
    bool isCall_;
    double T_;
    int m_;
};

// Asian
class ArthAsian : public PathDepOption {
public:
    ArthAsian(double T, int m, double K, bool isCall);
    double Payoff(lecture4::SamplePath& S);

protected:
    double K_;
};

// need an analytical pricer!
class GeomAsian : public PathDepOption {
public:
    GeomAsian(double T, int m, double K, bool isCall);
    double Payoff(lecture4::SamplePath& S);

protected:
    double K_;
};

// Vanilla
class Vanilla : public PathDepOption {
public:
    Vanilla(double T, int m, double K, bool isCall);
    double Payoff(lecture4::SamplePath& S);

protected:
    double K_;
};

// Barriers
class DoubleBarrierKO : public PathDepOption {
public:
    DoubleBarrierKO(double T, int m, double K, double Bup, double Bdown,
                    bool isCall);
    double Payoff(lecture4::SamplePath& S);

protected:
    double K_;
    double Bup_;
    double Bdown_;
};

class DoubleBarrierKI : public PathDepOption {
public:
    DoubleBarrierKI(double T, int m, double K, double Bup, double Bdown,
                    bool isCall);
    double Payoff(lecture4::SamplePath& S);

protected:
    double K_;
    double Bup_;
    double Bdown_;
};

}  // namespace lecture4