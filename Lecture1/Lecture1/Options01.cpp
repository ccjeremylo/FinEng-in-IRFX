//
//  Options01.cpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//

#include "Options01.hpp"

void getOptionsInputData(int& N, double& K) {
    std::cout << "Enter steps to expiry N: ";
    std::cin >> N;
    
    std::cout << "Enter strike price K: ";
    std::cin >> K;
    std::cout << std::endl;
}

double PriceByCRR(double S0, double U, double D, double R, int N, double K, double (*Payoff)(double z, double K)) {
    double q = riskNeutralProb(U,D,R);
    double Price[N+1];
    for (int i = 0 ; i <= N; i++) { // payoff
        *(Price+i) = Payoff( S(S0,U,D,N,i), K);
    }
    for ( int n = N - 1 ; n >= 0 ; n-- ) { // fill backwards by expectation
        for (int i = 0; i <= n; i++) { // requires double for loop to build entire tree
            *(Price+i) = ( q * (*(Price+i+1)) + (1 - q) * (*(Price+i)) ) / pow(1.+R,N);
        }
    }
    return *Price;
 }


double PriceAnalytic(double S0, double U, double D, double R, int N, double K, double (*Payoff)(double z, double K), std::string filename) {
    double q = riskNeutralProb(U, D, R);
    std::vector<double> PDF(N + 1);
    double PDF_Sum = 0.0;
    double *Price = new double[N + 1];
    double *S_T = new double[N + 1];
    double Sum = 0.0;
    
    std::string param = "_S0:"+std::to_string(S0) + "_U:"+std::to_string(U) + "_D:"+std::to_string(D) + "_R:"+std::to_string(R);
    std::string opt_param = "_N:"+std::to_string(N) + "_K:"+std::to_string(K);
    std::ofstream file(filename + param + opt_param + ".csv");
    file << "Position, S(T), Opt Price, PDF, ";
    file << ", U=" << U << "," << "D= "<< D << "," << "R= " << R;
    file << ", N=" << N << "," << "K= "<< K << "\n";
    
    for (int i=0; i<=N; i++)
    {
        S_T[i] = S(S0, U, D, N, i);
        Price[i] = Payoff(S_T[i], K);
    }
    for (int i=0; i<=N; i++)
    {
        PDF[i] = NewtonSymb(N, i) * pow(q, i) * pow(1 - q, N - i); // binomial distribution
        PDF_Sum += PDF[i];
        //std::cout << "i =" << i << " , PDF[i] = " << PDF[i] << std::endl;
        Sum += PDF[i] * Price[i];
        file << i << "," << S_T[i] << "," << Price[i] << "," << PDF[i] << "\n";
    }
    file.close();
    //std::cout << " PDF_Sum = " << PDF_Sum << std::endl ;
    double result = Sum / pow(1.+R,N); // expectation of discouted payoff
    delete [] Price;
    delete [] S_T;
    return result;
}

double CallPayoff(double S, double K) {
    if (S > K) {return S - K;}
    return 0.0;
}

double PutPayoff(double S, double K) {
    if (S < K) {return K - S;}
    return 0.0;
}
