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


int main(){
    
    double S0 = 100.0;
    double U = 0.05;
    double D = -0.05;
    double R = 0.03;
    //getInputData(S0, U, D, R);
    
    int N = 100; // number of years!?
    double K = 100.0;
    //getOptionsInputData(N, K);
    
    std::cout << "Risk neutral (up) prob q = " << riskNeutralProb(U,D,R) << std::endl;
    std::cout << "Moneyness (S/K) = " << S0/K << std::endl;
    
    std::cout << std::endl;
    
    // Call
    double priceCRR_call = PriceByCRR(S0, U, D, R, N, K, CallPayoff);
    std::cout << "Call option price by CRR     = " << priceCRR_call << std::endl;
    double price_call = PriceAnalytic(S0, U, D, R, N, K, CallPayoff, "pdf_call");
    std::cout << "Call option price (analytic) = " << price_call << std::endl;
    std::cout << std::endl;
    
    // Put
    double priceCRR_put = PriceByCRR(S0, U, D, R, N, K, PutPayoff);
    std::cout << "Put option price by CRR     = " << priceCRR_put << std::endl;
    double price_put = PriceAnalytic(S0, U, D, R, N, K, PutPayoff, "pdf_put");
    std::cout << "Put option price (analytic) = " << price_put << std::endl;
    
    std::cout << std::endl;
    
    std::ofstream myfile;
    myfile.open("example.txt");
    myfile << "test output!" << std::endl;
    myfile.close();
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}
