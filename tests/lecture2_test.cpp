#include <gtest/gtest.h>

#include "../src/Lecture2/BinModel02.hpp"
#include "../src/Lecture2/Options04.hpp"
#include "../src/Lecture2/BlackScholes.hpp"
#include "../src/Lecture2/payoff.hpp"
#include "../src/Lecture2/Options05.hpp"


TEST(L2, riskNeutralProbTest)
{
    double R = 0.02;
    double U = 0.1;
    double D = -0.1;
    double S0 = 100.0;

    lecture2::BinModel model = lecture2::BinModel(S0, U, D, R);
    EXPECT_EQ(model.GetR(), R) << "Invalid getter method for R";
    
    double q = model.RiskNeutralProb();
    EXPECT_TRUE(std::abs(q - (R-D) / (U-D)) < 0.0000001) << "Incorrect risk neutral prob function";
}

TEST(L2, equityTreeTest)
{
    double R = 0.02;
    double U = 0.1;
    double D = -0.1;
    double S0 = 100.0;

    lecture2::BinModel model = lecture2::BinModel(S0, U, D, R);

    double epsilon = 0.0000001;

    int N1 = 2;
    int i1 = 2;
    EXPECT_TRUE(std::abs(model.S(N1, i1) -S0*std::pow((1+U),i1)) < epsilon ) << "Trivial case failed!";
    int N2 = 5;
    int i2 = 3;
    EXPECT_TRUE(std::abs(model.S(N2, i2) -S0*std::pow((1+U),3)*std::pow((1+D),2)) < epsilon ) << "Non-trivial case failed!";
}

TEST(L2, vanillaCallPayOffs)
{
    EXPECT_EQ(lecture2::CallPayoff(10.1, 2.1), 8.0) << "Vanilla call ITM case failed!";
    EXPECT_EQ(lecture2::CallPayoff(2.3, 10.4), 0.0) << "Vanilla call OTM case failed!";
    EXPECT_EQ(lecture2::CallPayoff(100.2, 100.2), 0.0) << "Vanilla call ATM case failed!";
}

TEST(L2, vanillaPutPayOffs)
{
    EXPECT_EQ(lecture2::PutPayoff(10.1, 2.1), 0.0) << "Vanilla put OTM case failed!";
    EXPECT_EQ(lecture2::PutPayoff(2.3, 10.4), 10.4-2.3) << "Vanilla put ITM case failed!";
    EXPECT_EQ(lecture2::PutPayoff(100.2, 100.2), 0.0) << "Vanilla put ATM case failed!";
}


TEST(L2, lecture2_main)
{
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
    lecture2::BinModel BinModel1 = lecture2::BinModel(S0, U, D, R);

    lecture2::Call CallOption = lecture2::Call(N);
    lecture2::Put PutOption = lecture2::Put(N);

    lecture2::DoubleBarrierCall DBCall0 = lecture2::DoubleBarrierCall(N, 9999999.9, 0.0);
    lecture2::DoubleBarrierCall DBCall1 = lecture2::DoubleBarrierCall(N, B_upper, B_lower);

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
    double priceCRR_call = lecture2::PriceByCRR(BinModel1, N, K, lecture2::CallPayoff);
    std::cout << "Call option price by CRR     = " << priceCRR_call << std::endl;
    double price_call = lecture2::PriceAnalytic(BinModel1, N, K, lecture2::CallPayoff);
    std::cout << "Call option price (analytic) = " << price_call << std::endl;
    double price_bs_call = lecture2::call_price(S0, K, r, sigma, T);
    std::cout << "Call option price (BS)       = " << price_bs_call << std::endl;
    double bar_price = DBCall0.PriceByCRR(BinModel1, K);
    std::cout << "Call option price by DB call = " << bar_price << std::endl;
    std::cout << std::endl;
    
    // Vanilla Put
    double putobj_price =  PutOption.PriceByCRR(BinModel1, K);
    std::cout << "Put option price by CRR obj = " << putobj_price << std::endl;
    double priceCRR_put = lecture2::PriceByCRR(BinModel1, N, K, lecture2::PutPayoff);
    std::cout << "Put option price by CRR     = " << priceCRR_put << std::endl;
    double price_put = lecture2::PriceAnalytic(BinModel1, N, K, lecture2::PutPayoff);
    std::cout << "Put option price (analytic) = " << price_put << std::endl;
    double price_bs_put = lecture2::put_price(S0, K, r, sigma, T);
    std::cout << "Put option price (BS)       = " << price_bs_put << std::endl;
    std::cout << std::endl;
    
    // Double Barrier Option (Call)
    std::cout << "Upper Barrier = " << B_upper << std::endl;
    std::cout << "Lower Barrier = " << B_lower << std::endl;
    double bar_price_1 = DBCall1.PriceByCRR(BinModel1, K);
    std::cout << "Call option price by DB call = " << bar_price_1 << std::endl;
    std::cout << std::endl;

    EXPECT_EQ(1.0-1.0, 0.0) << "dummy test";
}
