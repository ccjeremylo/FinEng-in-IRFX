#include <gtest/gtest.h>

#include "../src/Lecture2/BlackScholes.hpp"
#include "../src/Lecture3/Options07.hpp"

TEST(L3, vanillaCallPayOffs) {
    double strike = 100.0;
    lecture3::Call callOp = lecture3::Call(strike, 20);
    EXPECT_EQ(callOp.Payoff(strike + 13.3), strike + 13.3 - strike)
        << "Vanilla call ITM case failed!";
    EXPECT_EQ(callOp.Payoff(strike), 0.0)
        << "Vanilla call ITM case failed!";
    EXPECT_EQ(callOp.Payoff(strike / 2.0), 0.0)
        << "Vanilla call ITM case failed!";
}

TEST(L3, vanillaPutPayOffs) {
    double strike = 132.0;
    lecture3::Put putOp = lecture3::Put(strike, 3);
    EXPECT_EQ(putOp.Payoff(strike / 3.1), strike - strike / 3.1)
        << "Vanilla call ITM case failed!";
    EXPECT_EQ(putOp.Payoff(strike), 0.0)
        << "Vanilla call ITM case failed!";
    EXPECT_EQ(putOp.Payoff(strike * 2.0), 0.0)
        << "Vanilla call ITM case failed!";
}

TEST(L3, numericalAndBSPrice) {
    double S0 = 250.0;

    double K = 263.0;
    double T = 6.1;  // option maturity

    int N = 500;       // number of steps
    double h = T / N;  // time step (years)

    double r = 0.05;
    double sigma = 0.35;
    double v = r + 0.5 * pow(sigma, 2);

    // this should be a function!
    double U = exp(v * h + sigma * pow(h, 0.5)) - 1;
    double D = exp(v * h - sigma * pow(h, 0.5)) - 1;
    double R = exp(r * h) - 1;

    double epsilon = 0.1;

    // Building the objects
    lecture2::BinModel BinModel1 = lecture2::BinModel(S0, U, D, R);
    lecture3::Call CallOption = lecture3::Call(K, N);
    lecture3::Put PutOption = lecture3::Put(K, N);

    // Vanilla Call
    double callopt_price = CallOption.PriceByCRR(BinModel1);
    double price_bs_call = lecture2::call_price(S0, K, r, sigma, T);
    double abs_err_call = std::abs(callopt_price - price_bs_call);
    double rel_err_call = abs_err_call / price_bs_call;
    EXPECT_TRUE(abs_err_call < epsilon);
    EXPECT_TRUE(rel_err_call < 0.001);

    // Vanilla Put
    double putopt_price = PutOption.PriceByCRR(BinModel1);
    double price_bs_put = lecture2::put_price(S0, K, r, sigma, T);
    double abs_err_put = std::abs(putopt_price - price_bs_put);
    double rel_err_put = abs_err_put / price_bs_put;
    EXPECT_TRUE(abs_err_put < epsilon);
    EXPECT_TRUE(rel_err_put < 0.001);
}

TEST(L3, americanOption) {
    double S0 = 240.0;

    double K = 233.0;
    double T = 2.9;  // option maturity

    int N = 500;       // number of steps
    double h = T / N;  // time step (years)

    double r = 0.03;
    double sigma = 0.4;
    double v = r + 0.5 * pow(sigma, 2);

    // this should be a function!
    double U = exp(v * h + sigma * pow(h, 0.5)) - 1;
    double D = exp(v * h - sigma * pow(h, 0.5)) - 1;
    double R = exp(r * h) - 1;

    // Building the objects
    lecture2::BinModel BinModel1 = lecture2::BinModel(S0, U, D, R);
    lecture3::Call CallOption = lecture3::Call(K, N);
    lecture3::Put PutOption = lecture3::Put(K, N);
    lecture3::Call CallOption2N = lecture3::Call(K, 2 * N);
    lecture3::Put PutOption2N = lecture3::Put(K, 2 * N);

    // American Call
    double price_bs_call = lecture2::call_price(S0, K, r, sigma, T);
    EXPECT_TRUE(price_bs_call > 0.0);
    double am_call_price = CallOption.PriceBySnell(BinModel1);
    EXPECT_TRUE(am_call_price > price_bs_call);
    double am_call_price_2N = CallOption2N.PriceBySnell(BinModel1);
    EXPECT_TRUE(am_call_price_2N > am_call_price);

    // American Put
    double price_bs_put = lecture2::put_price(S0, K, r, sigma, T);
    EXPECT_TRUE(price_bs_put > 0.0);
    double am_put_price = PutOption.PriceBySnell(BinModel1);
    EXPECT_TRUE(am_put_price > price_bs_put);
    double am_put_price_2N = PutOption2N.PriceBySnell(BinModel1);
    EXPECT_TRUE(am_put_price_2N > am_put_price);
}