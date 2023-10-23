//
//  Options05.hpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>

#include "payoff.hpp"
#include "BinModel02.hpp"

namespace lecture2 {

// Don't like this design, options should have no knowledge about the model
// Current design only accepts binomial model..!
// Additionally, K should be a property of the option, not the pricer
class EurOption
{
public:
    EurOption(int N);
    virtual double PriceByCRR(BinModel Model, double K);
    void SetPayoff(double (*Payoff)(double z, double K)) {
        Payoff_ = Payoff;
    }
    
protected:
    int N_;
    double (*Payoff_)(double z, double K);
};


// Poor design!! Using a payoff class would be better 
class Call: public EurOption
{
public:
    Call(int N);
    double GetK(){return K_;}

private:
    double K_;
};

// Poor design!! Using a payoff class would be better 
class Put: public EurOption
{
public:
    Put(int N);
    double GetK(){return K_;}

private:
    double K_;
};


// Poor design!! should be using a decorator...
class DoubleBarrierCall: public EurOption
{
public:
    DoubleBarrierCall(int N, double UpperB, double LowerB); // KO option
    double PriceByCRR(lecture2::BinModel Model, double K);
    double GetK(){return K_;}
    double GetUpperB(){return UpperB_;}
    double GetLowerB(){return LowerB_;}
    
private:
    double K_;
    double UpperB_;
    double LowerB_;
};

}