//
//  Options04.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include "Options04.hpp"

#include <vector>

void lecture2::getOptionsInputData(int& N, double& K) {
    std::cout << "Enter steps to expiry N: ";
    std::cin >> N;

    std::cout << "Enter strike price K: ";
    std::cin >> K;
    std::cout << std::endl;
}

double lecture2::PriceByCRR(lecture2::BinModel Model, int N, double K,
                            double (*Payoff)(double z, double K)) {
    double q = Model.RiskNeutralProb();
    double Price[N + 1];
    for (int i = 0; i <= N; i++) {  // payoff
        *(Price + i) = Payoff(Model.S(N, i), K);
    }
    for (int n = N - 1; n >= 0; n--) {  // fill backwards by expectation
        for (int i = 0; i <= n;
             i++) {  // requires double for loop to build entire tree
            *(Price + i) =
                (q * (*(Price + i + 1)) + (1 - q) * (*(Price + i))) /
                (1. + Model.GetR());
        }
    }
    return *Price;
}

// Binomial coefficient
double lecture2::NewtonSymb(int N, int i) {
    if (i < 0 || i > N)
        return 0;
    double result = 1;
    for (int k = 1; k <= i; k++) {
        result = result * (N - i + k) / k;
    }
    return result;
}

double lecture2::PriceAnalytic(lecture2::BinModel Model, int N, double K,
                               double (*Payoff)(double z, double K)) {
    double q = Model.RiskNeutralProb();
    std::vector<double> PDF(N + 1);
    double PDF_Sum = 0.0;
    double* Price = new double[N + 1];
    double* S_T = new double[N + 1];
    double Sum = 0.0;

    for (int i = 0; i <= N; i++) {
        S_T[i] = Model.S(N, i);
        Price[i] = Payoff(S_T[i], K);
    }
    for (int i = 0; i <= N; i++) {
        PDF[i] = lecture2::NewtonSymb(N, i) * pow(q, i) *
                 pow(1 - q, N - i);  // binomial distribution
        PDF_Sum += PDF[i];
        Sum += PDF[i] * Price[i];
    }
    // std::cout << " PDF_Sum = " << PDF_Sum << std::endl ;
    double result = Sum / pow(1. + Model.GetR(),
                              N);  // expectation of discouted payoff
    delete[] Price;
    delete[] S_T;
    return result;
}
