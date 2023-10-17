//
//  Options05.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include "Options05.hpp"

EurOption::EurOption(int N) : N_(N) {};

double EurOption::PriceByCRR(BinModel Model, double K) {
    double q = Model.RiskNeutralProb();
    double Price[N_+1];
    for (int i = 0 ; i <= N_; i++) { // payoff
        *(Price+i) = Payoff_( Model.S(N_,i), K);
    }
    for ( int n = N_ - 1 ; n >= 0 ; n-- ) { // fill backwards by expectation
        for (int i = 0; i <= n; i++) { // requires double for loop to build entire tree
            *(Price+i) = ( q * (*(Price+i+1)) + (1 - q) * (*(Price+i)) ) / (1.+ Model.GetR());
        }
    }
    return *Price;
 }


Call::Call(int N) : EurOption(N) {
    SetPayoff(CallPayoff);
}

Put::Put(int N) : EurOption(N) {
    SetPayoff(PutPayoff);
}

DoubleBarrierCall::DoubleBarrierCall(int N, double UpperB, double LowerB) : EurOption(N), UpperB_(UpperB), LowerB_(LowerB) {
    SetPayoff(CallPayoff);
}

double DoubleBarrierCall::PriceByCRR(BinModel Model, double K) {
    double q = Model.RiskNeutralProb();
    double Price[N_+1];
    for (int i = 0 ; i <= N_; i++) { // payoff
        double S_i = Model.S(N_,i);
        if (S_i >= UpperB_ || S_i <= LowerB_) {
            *(Price+i) = 0;
        } else {
            *(Price+i) = Payoff_(S_i, K);
        }
    }
    for ( int n = N_ - 1 ; n >= 0 ; n-- ) { // fill backwards by expectation
        for (int i = 0; i <= n; i++) { // requires double for loop to build entire tree
            double S_ni = Model.S(n,i);
            if (S_ni >= UpperB_ || S_ni <= LowerB_) {
                *(Price+i) = 0;
            } else {
                *(Price+i) = ( q * (*(Price+i+1)) + (1 - q) * (*(Price+i)) ) / (1.+ Model.GetR());
            }
        }
    }
    return *Price;
 }
