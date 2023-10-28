//
//  Options05.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <math.h>
#include <stdio.h>

#include <cmath>
#include <iostream>

#include "BinModel02.hpp"
#include "payoff.hpp"

namespace lecture2 {

// Don't like this design, options should have no knowledge about the model
// Current desigs only accepts binomial model..!
// Additionally, K should be a property of the option, not the pricer
class EurOption {
public:
    EurOption(int N);
    virtual double PriceByCRR(BinModel Model, double K);

protected:
    void SetPayoff(double (*Payoff)(double z, double K)) {
        Payoff_ = Payoff;
    }
    double SetTerminalPrice(double z, double K);
    double SetPrice(double upP, double downP, double q, double R);

    int N_;
    double (*Payoff_)(double z, double K);
};

// Poor design! Use a payoff class
class Call : public EurOption {
public:
    Call(int N);
    double GetK() { return K_; }

private:
    double K_;
};

// Poor design! Use a payoff class
class Put : public EurOption {
public:
    Put(int N);
    double GetK() { return K_; }

private:
    double K_;
};

// Poor design! Use a payoff class
class DigitalCall : public EurOption {
public:
    DigitalCall(int N);
    double GetK() { return K_; }

private:
    double K_;
};

class DigitalPut : public EurOption {
public:
    DigitalPut(int N);
    double GetK() { return K_; }

private:
    double K_;
};

/* //
// Using decorator
class DoubleBarrier : public EurOption
{
public:
    DoubleBarrier(EurOption *EurOptPtr, int N, double UpperB, double
LowerB);

    virtual double PriceByCRR(BinModel Model, double K) = 0;
    double GetUpperB() { return UpperB_; }
    double GetLowerB() { return LowerB_; }

protected:
    virtual double SetTerminalPrice(double z, double K) = 0;
    virtual double SetPrice(double upP, double downP, double q, double R) =
0;

    double K_;
    double UpperB_;
    double LowerB_;
    EurOption *EurOptPtr_;
};

class
DoubleBarrierKO
:
public
DoubleBarrier
{
public:
    DoubleBarrierKO(EurOption *EurOptPtr, int N, double UpperB, double
LowerB); double PriceByCRR(BinModel Model, double K);

protected:
    double SetTerminalPrice(double z, double K);
    double SetPrice(double upP, double downP, double q, double R);
};

class
DoubleBarrierKI
:
public
DoubleBarrier
{
public:
    DoubleBarrierKO(EurOption *EurOptPtr, int N, double UpperB, double
LowerB); double PriceByCRR(BinModel Model, double K);

protected:
    double SetTerminalPrice(double z, double K) = 0;
    double SetPrice(double upP, double downP, double q, double R);
}; */

// Poor design, try use a decorator
class DoubleBarrierCall : public EurOption {
public:
    DoubleBarrierCall(int N, double UpperB,
                      double LowerB);  // KO option
    double PriceByCRR(lecture2::BinModel Model, double K);
    double GetK() { return K_; }
    double GetUpperB() { return UpperB_; }
    double GetLowerB() { return LowerB_; }

private:
    double K_;
    double UpperB_;
    double LowerB_;
};

}  // namespace lecture2