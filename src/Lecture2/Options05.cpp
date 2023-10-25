//
//  Options05.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include "Options05.hpp"
#include <cassert>

lecture2::EurOption::EurOption(int N) : N_(N){};

double
    lecture2::EurOption::SetTerminalPrice(double z, double K) {
    return Payoff_(z, K);
};

double
    lecture2::EurOption::SetPrice(double upP, double downP, double q,
                                  double R) {
    return (q * upP + (1 - q) * downP) / (1. + R);
};

double
    lecture2::EurOption::PriceByCRR(lecture2::BinModel Model, double K) {
    double q = Model.RiskNeutralProb();
    double R = Model.GetR();
    double Price[N_ + 1];
    for (int i = 0; i <= N_; i++) {  // set terminal value
        Price[i] = SetTerminalPrice(Model.S(N_, i), K);
        //*(Price+i) = Payoff_( Model.S(N_,i), K);
    }
    for (int n = N_ - 1; n >= 0; n--) {  // fill backwards by expectation
        for (int i = 0; i <= n; i++) {
            Price[i] = SetPrice(Price[i + 1], Price[i], q, R);
            //*(Price+i) = ( q * (*(Price+i+1)) + (1 - q) *
            //(*(Price+i)) ) / (1.+
            // Model.GetR());
        }
    }
    return *Price;
}

lecture2::Call::Call(int N) : lecture2::EurOption(N) { SetPayoff(CallPayoff); }

lecture2::Put::Put(int N) : lecture2::EurOption(N) { SetPayoff(PutPayoff); }

lecture2::DigitalCall::DigitalCall(int N) : lecture2::EurOption(N) {
    SetPayoff(DigitalCallPayoff);
}

lecture2::DigitalPut::DigitalPut(int N) : lecture2::EurOption(N) {
    SetPayoff(DigitalPutPayoff);
}

/* // barrier
lecture2::DoubleBarrier::DoubleBarrier(lecture2::EurOption *EurOptPtr, int N,
                                       double UpperB, double LowerB)
    : lecture2::EurOption(N),
      EurOptPtr_(EurOptPtr),
      UpperB_(UpperB),
      LowerB_(LowerB) {
    EurOptPtr->SetPayoff();
} */

lecture2::DoubleBarrierCall::DoubleBarrierCall(int N, double UpperB,
                                               double LowerB)
    : lecture2::EurOption(N), UpperB_(UpperB), LowerB_(LowerB) {
    assert(UpperB > LowerB);
    SetPayoff(CallPayoff);
}

double
    lecture2::DoubleBarrierCall::PriceByCRR(lecture2::BinModel Model,
                                            double K) {
    double q = Model.RiskNeutralProb();
    double Price[N_ + 1];
    for (int i = 0; i <= N_; i++) {
        double S_i = Model.S(N_, i);
        if (S_i >= UpperB_ || S_i <= LowerB_) {
            *(Price + i) = 0;
        } else {
            *(Price + i) = Payoff_(S_i, K);
        }
        for (int n = N_ - 1; n >= 0; n--) {  // fill backwards by expectation
            for (int i = 0; i <= n;
                 i++) {  // requires nested for-loop to build entire tree
                double S_ni = Model.S(n, i);
                if (S_ni >= UpperB_ || S_ni <= LowerB_) {
                    *(Price + i) = 0;
                } else {
                    *(Price + i) =
                        (q * (*(Price + i + 1)) + (1 - q) * (*(Price + i))) /
                        (1. + Model.GetR());
                }
            }
        }
    }
    return *Price;
}
