#include <gtest/gtest.h>

#include "../src/Lecture2/BinModel02.hpp"
#include "../src/Lecture2/BlackScholes.hpp"
#include "../src/Lecture2/Options04.hpp"
#include "../src/Lecture2/Options05.hpp"
#include "../src/Lecture2/payoff.hpp"

TEST(L2, riskNeutralProbTest) {
    double R = 0.02;
    double U = 0.1;
    double D = -0.1;
    double S0 = 100.0;

    lecture2::BinModel model = lecture2::BinModel(S0, U, D, R);
    EXPECT_EQ(model.GetR(), R) << "Invalid getter method for R";

    double q = model.RiskNeutralProb();
    EXPECT_NEAR(q, (R - D) / (U - D), 0.0000001)
        << "Incorrect risk neutral prob "
           "function";
}

TEST(L2, equityTreeTest) {
    double R = 0.02;
    double U = 0.1;
    double D = -0.1;
    double S0 = 100.0;

    lecture2::BinModel model = lecture2::BinModel(S0, U, D, R);

    double epsilon = 0.0000001;

    int N1 = 2;
    int i1 = 2;
    EXPECT_NEAR(model.S(N1, i1), S0 * std::pow((1 + U), i1), epsilon)
        << "Trivial case failed!";
    int N2 = 5;
    int i2 = 3;
    EXPECT_NEAR(model.S(N2, i2),
                S0 * std::pow((1 + U), 3) * std::pow((1 + D), 2), epsilon)
        << "Non-trivial case failed!";
}

TEST(L2, vanillaCallPayOffs) {
    EXPECT_EQ(lecture2::CallPayoff(10.1, 2.1), 8.0)
        << "Vanilla call ITM case failed!";
    EXPECT_EQ(lecture2::CallPayoff(2.3, 10.4), 0.0)
        << "Vanilla call OTM case failed!";
    EXPECT_EQ(lecture2::CallPayoff(100.2, 100.2), 0.0)
        << "Vanilla call ATM case failed!";
}

TEST(L2, vanillaPutPayOffs) {
    EXPECT_EQ(lecture2::PutPayoff(10.1, 2.1), 0.0)
        << "Vanilla put OTM case failed!";
    EXPECT_EQ(lecture2::PutPayoff(2.3, 10.4), 10.4 - 2.3)
        << "Vanilla put ITM case failed!";
    EXPECT_EQ(lecture2::PutPayoff(100.2, 100.2), 0.0)
        << "Vanilla put ATM case failed!";
}

TEST(L2, digitalCallPayOffs) {
    EXPECT_EQ(lecture2::DigitalCallPayoff(10.1, 2.1), 1.0)
        << "Digital call ITM case failed!";
    EXPECT_EQ(lecture2::DigitalCallPayoff(2.3, 10.4), 0.0)
        << "Digital call OTM case failed!";
    EXPECT_EQ(lecture2::DigitalCallPayoff(100.2, 100.2), 0.0)
        << "Digital call ATM case failed!";
}

TEST(L2, digitalPutPayOffs) {
    EXPECT_EQ(lecture2::DigitalPutPayoff(10.1, 2.1), 0.0)
        << "Digital put OTM case failed!";
    EXPECT_EQ(lecture2::DigitalPutPayoff(2.3, 10.4), 1.0)
        << "Digital put ITM case failed!";
    EXPECT_EQ(lecture2::DigitalPutPayoff(100.2, 100.2), 0.0)
        << "Digital put ATM case failed!";
}

TEST(L2, CRRBinomialTest) {
    double S0 = 110.0;
    double r = 0.001;
    double sigma = 0.2;
    double v = r + 0.5 * pow(sigma, 2);

    double K = 100.0;
    double T = 10;  // option maturity

    int N = 50;        // number of steps
    double h = T / N;  // time step (years)

    double U = exp(v * h + sigma * pow(h, 0.5)) - 1;
    double D = exp(v * h - sigma * pow(h, 0.5)) - 1;
    double R = exp(r * h) - 1;

    double epsilon = 0.000001;

    // Building the objects
    lecture2::BinModel BinModel1 = lecture2::BinModel(S0, U, D, R);
    lecture2::Call CallOption = lecture2::Call(N);
    lecture2::Put PutOption = lecture2::Put(N);

    // Vanilla Call
    double callobj_price = CallOption.PriceByCRR(BinModel1, K);
    double priceCRR_call =
        lecture2::PriceByCRR(BinModel1, N, K, lecture2::CallPayoff);
    double price_call =
        lecture2::PriceAnalytic(BinModel1, N, K, lecture2::CallPayoff);
    EXPECT_NEAR(callobj_price, priceCRR_call, epsilon);
    EXPECT_NEAR(callobj_price, price_call, epsilon);

    // Vanilla Put
    double putobj_price = PutOption.PriceByCRR(BinModel1, K);
    double priceCRR_put =
        lecture2::PriceByCRR(BinModel1, N, K, lecture2::PutPayoff);
    double price_put =
        lecture2::PriceAnalytic(BinModel1, N, K, lecture2::PutPayoff);
    EXPECT_NEAR(putobj_price, priceCRR_put, epsilon);
    EXPECT_NEAR(putobj_price, price_put, epsilon);
}

TEST(L2, numericalAndBSPrice) {
    double S0 = 250.0;

    double K = 263.0;
    double T = 6.1;  // option maturity

    int N = 500;       // number of steps
    double h = T / N;  // time step (years)

    double r = 0.05;
    double sigma = 0.35;
    double v = r + 0.5 * pow(sigma, 2);

    double U = exp(v * h + sigma * pow(h, 0.5)) - 1;
    double D = exp(v * h - sigma * pow(h, 0.5)) - 1;
    double R = exp(r * h) - 1;

    double epsilon = 0.1;

    // Building the objects
    lecture2::BinModel BinModel1 = lecture2::BinModel(S0, U, D, R);
    lecture2::Call CallOption = lecture2::Call(N);
    lecture2::Put PutOption = lecture2::Put(N);

    // Vanilla Call
    double callobj_price = CallOption.PriceByCRR(BinModel1, K);
    double price_bs_call = lecture2::call_price(S0, K, r, sigma, T);
    double abs_err_call = std::abs(callobj_price - price_bs_call);
    double rel_err_call = abs_err_call / price_bs_call;
    EXPECT_TRUE(abs_err_call < epsilon);
    EXPECT_TRUE(rel_err_call < 0.001);

    // Vanilla Put
    double putobj_price = PutOption.PriceByCRR(BinModel1, K);
    double price_bs_put = lecture2::put_price(S0, K, r, sigma, T);
    double abs_err_put = std::abs(putobj_price - price_bs_put);
    double rel_err_put = abs_err_put / price_bs_put;
    EXPECT_TRUE(abs_err_put < epsilon);
    EXPECT_TRUE(rel_err_put < 0.001);
}

TEST(L2, doubleBarrierKOTest) {
    double S0 = 100.0;

    double K = 121.0;
    double T = 2.6;  // option maturity

    int N = 200;       // number of steps
    double h = T / N;  // time step (years)

    double r = 0.05;
    double sigma = 0.35;
    double v = r + 0.5 * pow(sigma, 2);

    double U = exp(v * h + sigma * pow(h, 0.5)) - 1;
    double D = exp(v * h - sigma * pow(h, 0.5)) - 1;
    double R = exp(r * h) - 1;

    double B_upper = 135;  // top barrier
    double B_lower = 50;   // bottom barrier

    double epsilon = 0.00001;

    // Building the classes
    lecture2::BinModel BinModel1 = lecture2::BinModel(S0, U, D, R);
    lecture2::Call CallOption = lecture2::Call(N);
    lecture2::DoubleBarrierCall DBCall0 =
        lecture2::DoubleBarrierCall(N, 999999999.9, 0.0);
    lecture2::DoubleBarrierCall DBCall1 =
        lecture2::DoubleBarrierCall(N, B_upper, B_lower);

    // Vanilla Call
    double callobj_price = CallOption.PriceByCRR(BinModel1, K);
    double bar_price = DBCall0.PriceByCRR(BinModel1, K);
    EXPECT_NEAR(callobj_price, bar_price, epsilon);

    // Double Barrier Option (Call)
    double bar_price_1 = DBCall1.PriceByCRR(BinModel1, K);
    EXPECT_TRUE(bar_price_1 < bar_price);
}
