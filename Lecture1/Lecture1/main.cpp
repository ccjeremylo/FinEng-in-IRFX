//
//  main.cpp
//  Lecture1
//
//  Created by Jeremy Lo on 08/10/2023.
//

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "BinModel01.hpp"
#include "Options01.hpp"
#include "BlackScholes.hpp"


int main(){
    
    double S0 = 110.0;
    
    
    double K = 100.0;
    double T = 10; // option maturity
    
    int N = 50; // number of steps
    double h = T/N; // time step (years)
    
    double r = 0.0;
    double sigma = 0.2;
    double v = r + 0.5 * pow(sigma,2);
    
    double U = exp(v * h + sigma * pow(h, 0.5)) -1;
    double D = exp(v * h - sigma * pow(h, 0.5)) -1;
    double R = exp(r * h) -1;
    //getInputData(S0, U, D, R);
    
    
    //getOptionsInputData(N, K);
    
    std::cout << "Risk neutral (up) prob q = " << riskNeutralProb(U,D,R) << std::endl;
    std::cout << "Moneyness (S/K) = " << S0/K << std::endl;
    
    std::cout << std::endl;
    
    // Call
    double priceCRR_call = PriceByCRR(S0, U, D, R, N, K, CallPayoff);
    std::cout << "Call option price by CRR     = " << priceCRR_call << std::endl;
    double price_call = PriceAnalytic(S0, U, D, R, N, K, CallPayoff, "pdf_call");
    std::cout << "Call option price (analytic) = " << price_call << std::endl;
    double price_bs_call = call_price(S0, K, r, sigma, T);
    std::cout << "Call option price (BS) = " << price_bs_call << std::endl;
    std::cout << std::endl;
    
    // Put
    double priceCRR_put = PriceByCRR(S0, U, D, R, N, K, PutPayoff);
    std::cout << "Put option price by CRR     = " << priceCRR_put << std::endl;
    double price_put = PriceAnalytic(S0, U, D, R, N, K, PutPayoff, "pdf_put");
    std::cout << "Put option price (analytic) = " << price_put << std::endl;
    double price_bs_put = put_price(S0, K, r, sigma, T);
    std::cout << "Put option price (BS) = " << price_bs_put << std::endl;
    std::cout << std::endl;
    
    std::ofstream myfile;
    myfile.open("example.txt");
    myfile << "test output!" << std::endl;
    myfile.close();
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}
