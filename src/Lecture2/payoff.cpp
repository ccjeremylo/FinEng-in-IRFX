//
//  payoff.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include "payoff.hpp"

double lecture2::CallPayoff(double S, double K) {
    if (S > K) {return S - K;}
    return 0.0;
}

double lecture2::PutPayoff(double S, double K) {
    if (S < K) {return K - S;}
    return 0.0;
}

double lecture2::DigitalCallPayoff(double S, double K) {
    if (S > K) {return 1.0;}
    return 0.0;
}

double lecture2::DigitalPutPayoff(double S, double K) {
    if (S < K) {return 1.0;}
    return 0.0;
}