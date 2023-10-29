#include <gtest/gtest.h>

#include "../src/Lecture2/BlackScholes.hpp"
#include "../src/Lecture4/BSModel01.hpp"
#include "../src/Lecture4/PathDepOption01.hpp"
#include "../src/Lecture4/RNGenerator.hpp"

TEST(L4, BoxMullerSeed) {
    int seed1 = 1;
    int seed2 = 13;

    rng::BoxMueller BM1a = rng::BoxMueller(seed1);
    rng::BoxMueller BM1b = rng::BoxMueller(seed1);
    rng::BoxMueller BM2a = rng::BoxMueller(seed2);
    rng::BoxMueller BM2b = rng::BoxMueller(seed2);

    EXPECT_EQ(BM1a.GetSeed(), seed1);
    EXPECT_EQ(BM2a.GetSeed(), seed2);

    double G1a = BM1a.Gauss();
    EXPECT_EQ(G1a, BM1b.Gauss());
    EXPECT_TRUE(G1a != BM1a.Gauss());

    double G2a = BM2a.Gauss();
    EXPECT_EQ(G2a, BM2b.Gauss());
    EXPECT_TRUE(G2a != G1a);

    EXPECT_EQ(BM1a.GetSeed(), seed1 + 4);
    EXPECT_EQ(BM2b.GetSeed(), seed2 + 2);
}

TEST(L4, BSModelZeroVol) {
    rng::BoxMueller BM = rng::BoxMueller(1);

    double S0 = 100.0;
    double r = 0.03;
    // zero vol
    lecture4::BSModel Model = lecture4::BSModel(S0, r, 0.0, BM);
    EXPECT_EQ(Model.GetR(), r);

    int m = 5;
    double T = 3.2;
    lecture4::SamplePath S(m);
    Model.GenerateSamplePath(T, m, S);

    double St = S0;
    for (int i = 0; i < m; i++) {
        EXPECT_NEAR(S[i], St, 1.0e-8)
            << "index i = " << i << ": S[i] = " << S[i]
            << ", expected: " << St << std::endl;
        St *= exp(r * T / m);
    }
}

TEST(L4, BSModelZeroVol2) {
    rng::BoxMueller BM = rng::BoxMueller(1);

    double S0 = 100.0;
    double r = 0.03;
    // zero vol
    lecture4::BSModel Model = lecture4::BSModel(S0, r, 0.0, BM);
    EXPECT_EQ(Model.GetR(), r);

    int m = 5;
    double T = 3.2;
    lecture4::SamplePath S(m);
    Model.GenerateSamplePath(T, m, S);

    double St = S0;
    for (int i = 0; i < m; i++) {
        EXPECT_NEAR(S[i], St, 1.0e-8)
            << "index i = " << i << ": S[i] = " << S[i]
            << ", expected: " << St << std::endl;
        St *= exp(r * T / m);
    }
}

TEST(L4, vanillaCallPayOffs) {
    double K = 100.0;
    int m = 3;
    lecture4::Vanilla Call = lecture4::Vanilla(2.3, m, K, true);

    lecture4::SamplePath S(m);
    S[m] = 10;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1e-7)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
    S[m] = 106.3;
    EXPECT_NEAR(Call.Payoff(S), S[m] - K, 1e-7)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
}

TEST(L4, vanillaPutPayOffs) {
    double K = 105.03;
    int m = 6;
    lecture4::Vanilla Put = lecture4::Vanilla(9.3, m, K, false);

    lecture4::SamplePath S(m);
    S[m] = 10.36;
    EXPECT_NEAR(Put.Payoff(S), K - S[m], 1e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
    S[m] = 106.3;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
}