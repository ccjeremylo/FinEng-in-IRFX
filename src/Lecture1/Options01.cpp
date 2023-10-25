//
//  Options01.cpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//

#include "Options01.hpp"

void lecture1::getOptionsInputData(int& N, double& K) {
    std::cout << "Enter steps to expiry N: ";
    std::cin >> N;

    std::cout << "Enter strike price K: ";
    std::cin >> K;
    std::cout << std::endl;
}

double lecture1::PriceByCRR(double S0, double U, double D, double R, int N,
                            double K, double (*Payoff)(double z, double K)) {
    double q = lecture1::riskNeutralProb(U, D, R);
    double Price[N + 1];
    for (int i = 0; i <= N; i++) {  // payoff
        *(Price + i) = Payoff(S(S0, U, D, N, i), K);
    }
    for (int n = N - 1; n >= 0; n--) {  // fill backwards by expectation
        for (int i = 0; i <= n;
             i++) {  // requires double for loop to build entire tree
            *(Price + i) =
                (q * (*(Price + i + 1)) + (1 - q) * (*(Price + i))) / (1. + R);
        }
    }
    return *Price;
}

double lecture1::PriceAnalytic(double S0, double U, double D, double R, int N,
                               double K, double (*Payoff)(double z, double K)) {
    double q = lecture1::riskNeutralProb(U, D, R);
    std::vector<double> PDF(N + 1);
    double PDF_Sum = 0.0;
    double* Price = new double[N + 1];
    double* S_T = new double[N + 1];
    double Sum = 0.0;

    for (int i = 0; i <= N; i++) {
        S_T[i] = S(S0, U, D, N, i);
        Price[i] = Payoff(S_T[i], K);
    }
    for (int i = 0; i <= N; i++) {
        PDF[i] = lecture1::NewtonSymb(N, i) * pow(q, i) *
                 pow(1 - q, N - i);  // binomial distribution
        PDF_Sum += PDF[i];
        Sum += PDF[i] * Price[i];
    }

    // std::cout << " PDF_Sum = " << PDF_Sum << std::endl ;
    double result = Sum / pow(1. + R, N);  // expectation of discouted payoff
    delete[] Price;
    delete[] S_T;
    return result;
}

double lecture1::CallPayoff(double S, double K) {
    if (S > K) {
        return S - K;
    }
    return 0.0;
}

double lecture1::PutPayoff(double S, double K) {
    if (S < K) {
        return K - S;
    }
    return 0.0;
}
