//
//  pricing_functions.cpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//

#include "BinModel01.hpp"

void lecture1::getInputData(double &S0, double &U, double &D, double &R) {
    std::cout << "Enter S0: ";
    std::cin >> S0;

    std::cout << "Enter U: ";
    std::cin >> U;

    std::cout << "Enter D: ";
    std::cin >> D;

    std::cout << "Enter R: ";
    std::cin >> R;

    // should really be done in a constructor!
    if (S0 <= 0 || U <= -1.0 || D <= -1.0 || R <= -1.0 || U <= D) {
        throw std::invalid_argument(
            "Illegal data range! Program is terminated");
    }
    // check for arb
    if (R <= D || R >= U) {
        throw std::invalid_argument("Arb opp exists! Program is terminated");
    }
}

// Binomial coefficient
double lecture1::NewtonSymb(int N, int i) {
    if (i < 0 || i > N)
        return 0;
    double result = 1;
    for (int k = 1; k <= i; k++) {
        result = result * (N - i + k) / k;
    }
    return result;
}

double lecture1::riskNeutralProb(const double &U, const double &D,
                                 const double &R) {
    return (R - D) / (U - D);
}

double lecture1::S(const double &S0, const double &U, const double &D,
                   const int &N, const int &i) {
    return S0 * std::pow(1 + U, i) * std::pow(1 + D, N - i);
}
