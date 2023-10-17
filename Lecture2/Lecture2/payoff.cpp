//
//  payoff.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include "payoff.hpp"

double CallPayoff(double S, double K) {
    if (S > K) {return S - K;}
    return 0.0;
}

double PutPayoff(double S, double K) {
    if (S < K) {return K - S;}
    return 0.0;
}

double DoublePayoff(double S, double K) {
    if (S < K) {return K - S;}
    return 0.0;
}
