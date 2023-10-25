//
//  BinModel.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include "BinModel02.hpp"

double lecture2::BinModel::RiskNeutralProb() { return (R_ - D_) / (U_ - D_); }

double lecture2::BinModel::S(int n, int i) {
    return S0_ * pow(1 + U_, i) * pow(1 + D_, n - i);
}

double lecture2::BinModel::GetR() { return R_; }

lecture2::BinModel::BinModel(double S0, double U, double D, double R)
    : S0_(S0), U_(U), D_(D), R_(R) {
    if (S0_ <= 0 || U_ <= -1.0 || D_ <= -1.0 || R_ <= -1.0 || U_ <= D) {
        throw std::invalid_argument("Illegal data range!");
    }
    // check for arb
    if (R_ <= D || R_ >= U) {
        throw std::invalid_argument("Arb opp exists!");
    }

    std::cout << "Input data checked - no arbitrage oppertunities detected"
              << std::endl;
};
