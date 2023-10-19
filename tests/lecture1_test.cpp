#include <gtest/gtest.h>

#include "../src/Lecture1/BinModel01.hpp"
#include "../src/Lecture1/BlackScholes.hpp"
#include "../src/Lecture1/Options01.hpp"


TEST(FINENG, riskNeutralProbTest)
{
    double R = 0.02;
    double U = 0.1;
    double D = -0.1;

    double q = lecture1::riskNeutralProb(U,D,R);
    EXPECT_TRUE(std::abs(q - (R-D) / (U-D)) < 0.0000001) << "Incorrect risk neutral prob function";
}

TEST(L1, binomialCoeffTest)
{
    EXPECT_EQ(lecture1::NewtonSymb(1, 1), 1) << "Trivial case failed!";
    EXPECT_EQ(lecture1::NewtonSymb(10, 1), 10) << "Trivial case failed!";
    EXPECT_EQ(lecture1::NewtonSymb(15, 6), 5005) << "Non-rrivial case failed!";
}

TEST(L1, equityTreeTest)
{
    double S0 = 10.0;
    double U = 0.1;
    double D = -0.1;

    double epsilon = 0.000001;

    int N1 = 2;
    int i1 = 2;
    EXPECT_TRUE(std::abs(lecture1::S(S0, U, D, N1, i1) -S0*std::pow((1+U),i1)) < epsilon ) << "Trivial case failed!";
    int N2 = 5;
    int i2 = 3;
    EXPECT_TRUE(std::abs(lecture1::S(S0, U, D, N2, i2) -S0*std::pow((1+U),3)*std::pow((1+D),2)) < epsilon ) << "Non-trivial case failed!";
}

TEST(L1, vanillaCallPayOffs)
{
    EXPECT_EQ(lecture1::CallPayoff(10.1, 2.1), 8.0) << "Vanilla call ITM case failed!";
    EXPECT_EQ(lecture1::CallPayoff(2.3, 10.4), 0.0) << "Vanilla call OTM case failed!";
    EXPECT_EQ(lecture1::CallPayoff(100.2, 100.2), 0.0) << "Vanilla call ATM case failed!";
}

TEST(L1, vanillaPutPayOffs)
{
    EXPECT_EQ(lecture1::PutPayoff(10.1, 2.1), 0.0) << "Vanilla put OTM case failed!";
    EXPECT_EQ(lecture1::PutPayoff(2.3, 10.4), 10.4-2.3) << "Vanilla put ITM case failed!";
    EXPECT_EQ(lecture1::PutPayoff(100.2, 100.2), 0.0) << "Vanilla put ATM case failed!";
}

TEST(L1, CRRBinomialTest)
{
    double S0 = 110.0;
    double r = 0.001;
    double sigma = 0.2;
    double v = r + 0.5 * pow(sigma,2);

    double K = 100.0;
    double T = 10; // option maturity
    
    int N = 50; // number of steps
    double h = T/N; // time step (years)
    
    double U = exp(v * h + sigma * pow(h, 0.5)) -1;
    double D = exp(v * h - sigma * pow(h, 0.5)) -1;
    double R = exp(r * h) -1;

    double epsilon = 0.000001;
    
    // Call
    double priceCRR_call = lecture1::PriceByCRR(S0, U, D, R, N, K, lecture1::CallPayoff);
    double price_call = lecture1::PriceAnalytic(S0, U, D, R, N, K, lecture1::CallPayoff);
    EXPECT_TRUE(std::abs(priceCRR_call -price_call) < epsilon);
    
    // Put
    double priceCRR_put = lecture1::PriceByCRR(S0, U, D, R, N, K, lecture1::PutPayoff);
    double price_put = lecture1::PriceAnalytic(S0, U, D, R, N, K, lecture1::PutPayoff);
    EXPECT_TRUE(std::abs(priceCRR_put -price_put) < epsilon);
    
}

TEST(L1, numericalAndBSPrice)
{
    double S0 = 80.0;
    double r = 0.02;
    double sigma = 0.45;
    double v = r + 0.5 * pow(sigma,2);

    double K = 90.0;
    double T = 6.3; // option maturity
    
    int N = 500; // number of steps
    double h = T/N; // time step (years)
    
    double U = exp(v * h + sigma * pow(h, 0.5)) -1;
    double D = exp(v * h - sigma * pow(h, 0.5)) -1;
    double R = exp(r * h) -1;

    double epsilon = 0.1;
    
    // Call
    double priceCRR_call = lecture1::PriceByCRR(S0, U, D, R, N, K, lecture1::CallPayoff);
    double price_bs_call = lecture1::call_price(S0, K, r, sigma, T);
    double abs_err_call = std::abs(priceCRR_call -price_bs_call);
    double rel_err_call = abs_err_call / price_bs_call;
    EXPECT_TRUE(abs_err_call < epsilon);
    EXPECT_TRUE(rel_err_call < 0.0001);
    
    // Put
    double priceCRR_put = lecture1::PriceByCRR(S0, U, D, R, N, K, lecture1::PutPayoff);
    double price_bs_put = lecture1::put_price(S0, K, r, sigma, T);
    double abs_err_put = std::abs(priceCRR_put -price_bs_put);
    double rel_err_put = abs_err_put / price_bs_put;
    EXPECT_TRUE(abs_err_put < epsilon);
    EXPECT_TRUE(rel_err_put < 0.0001);
}