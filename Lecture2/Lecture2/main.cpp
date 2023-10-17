//
//  main.cpp
//  Lecture2
//
//  Created by Jeremy Lo on 17/10/2023.
//

#include <iostream>
#include "BinModel02.hpp"
#include "Options04.hpp"
#include "BlackScholes.hpp"
#include "payoff.hpp"
#include "Options05.hpp"

double S0 = 90.0;

double K = 100.0;
double T = 5; // option maturity

int N = 20; // number of steps
double h = T/N; // time step (years)

double r = 0.01;
double sigma = 0.2;
double v = r + 0.5 * pow(sigma,2);

double U = exp(v * h + sigma * pow(h, 0.5)) -1;
double D = exp(v * h - sigma * pow(h, 0.5)) -1;
double R = exp(r * h) -1;

double B_upper = 130; // top barrier
double B_lower = 50;  // bottom barrier

// Building the classes
BinModel BinModel1 = BinModel(S0, U, D, R);

Call CallOption = Call(N);
Put PutOption = Put(N);

DoubleBarrierCall DBCall0 = DoubleBarrierCall(N, 9999999.9, 0.0);
DoubleBarrierCall DBCall1 = DoubleBarrierCall(N, B_upper, B_lower);

int main() {
    std::cout << std::endl;
    
    std::cout << "Spot                     = " << S0 << std::endl;
    std::cout << "Strike                   = " << K << std::endl;
    std::cout << "Moneyness (S/K)          = " << S0/K << std::endl;
    std::cout << "Risk-free short rate (r) = " << r << std::endl;
    std::cout << "Time to maturity (T)     = " << T << std::endl;
    std::cout << "Eq vol (sigma)           = " << sigma << std::endl;
    std::cout << std::endl;
    
    std::cout << "Risk neutral (up) prob q = " << BinModel1.RiskNeutralProb() << std::endl;
    std::cout << "Number of time steps (N) = " << N << std::endl;
    std::cout << std::endl;
    
    // Vanilla Call
    double callobj_price = CallOption.PriceByCRR(BinModel1, K);
    std::cout << "Call option price by CRR obj = " << callobj_price << std::endl;
    double priceCRR_call = PriceByCRR(BinModel1, N, K, CallPayoff);
    std::cout << "Call option price by CRR     = " << priceCRR_call << std::endl;
    double price_call = PriceAnalytic(BinModel1, N, K, CallPayoff);
    std::cout << "Call option price (analytic) = " << price_call << std::endl;
    double price_bs_call = call_price(S0, K, r, sigma, T);
    std::cout << "Call option price (BS)       = " << price_bs_call << std::endl;
    double bar_price = DBCall0.PriceByCRR(BinModel1, K);
    std::cout << "Call option price by DB call = " << bar_price << std::endl;
    std::cout << std::endl;
    
    // Vanilla Put
    double putobj_price =  PutOption.PriceByCRR(BinModel1, K);
    std::cout << "Put option price by CRR obj = " << putobj_price << std::endl;
    double priceCRR_put = PriceByCRR(BinModel1, N, K, PutPayoff);
    std::cout << "Put option price by CRR     = " << priceCRR_put << std::endl;
    double price_put = PriceAnalytic(BinModel1, N, K, PutPayoff);
    std::cout << "Put option price (analytic) = " << price_put << std::endl;
    double price_bs_put = put_price(S0, K, r, sigma, T);
    std::cout << "Put option price (BS)       = " << price_bs_put << std::endl;
    std::cout << std::endl;
    
    // Double Barrier Option (Call)
    std::cout << "Upper Barrier = " << B_upper << std::endl;
    std::cout << "Lower Barrier = " << B_lower << std::endl;
    double bar_price_1 = DBCall1.PriceByCRR(BinModel1, K);
    std::cout << "Call option price by DB call = " << bar_price_1 << std::endl;
    std::cout << std::endl;
}
