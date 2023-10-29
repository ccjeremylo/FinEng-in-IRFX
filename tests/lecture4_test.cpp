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
    S[m - 1] = 10;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1e-7)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
    S[m - 1] = 106.3;
    EXPECT_NEAR(Call.Payoff(S), S[m - 1] - K, 1e-7)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
}

TEST(L4, vanillaPutPayOffs) {
    double K = 105.03;
    int m = 6;
    lecture4::Vanilla Put = lecture4::Vanilla(9.3, m, K, false);

    lecture4::SamplePath S(m);
    S[m - 1] = 10.36;
    EXPECT_NEAR(Put.Payoff(S), K - S[m - 1], 1e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
    S[m - 1] = 106.3;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
}

TEST(L4, doubleKOCallPayOffs) {
    double K = 100.0;
    int m = 3;
    double Bup = 120.0;
    double Bdown = 80.0;
    lecture4::DoubleBarrierKO Call =
        lecture4::DoubleBarrierKO(2.3, m, K, Bup, Bdown, true);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 70.0;
    S[2] = 106.0;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (KO): " << Call.Payoff(S) << std::endl;
    S[1] = 110.0;
    EXPECT_NEAR(Call.Payoff(S), 6.0, 1.0e-8)
        << "Terminal payoff (ITM): " << Call.Payoff(S) << std::endl;
    S[1] = 130.0;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (KO): " << Call.Payoff(S) << std::endl;
    S[1] = 119.999999;
    S[2] = K;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (ATM): " << Call.Payoff(S) << std::endl;
    S[2] = 5.0;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (OTM): " << Call.Payoff(S) << std::endl;
}

TEST(L4, doubleKOPutPayOffs) {
    double K = 100.0;
    int m = 3;
    double Bup = 120.0;
    double Bdown = 80.0;
    lecture4::DoubleBarrierKO Put =
        lecture4::DoubleBarrierKO(2.3, m, K, Bup, Bdown, false);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 79.99;
    S[2] = 96.0;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff: (KO)" << Put.Payoff(S) << std::endl;
    S[1] = 110.0;
    EXPECT_NEAR(Put.Payoff(S), 4.0, 1.0e-8)
        << "Terminal payoff (ITM): " << Put.Payoff(S) << std::endl;
    S[1] = 120.0;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff: (KO)" << Put.Payoff(S) << std::endl;
    S[1] = 80.00001;
    S[2] = K;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (ATM): " << Put.Payoff(S) << std::endl;
    S[2] = 102.9;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (OTM): " << Put.Payoff(S) << std::endl;
}

// add test for KI
TEST(L4, doubleKICallPayOffs) {
    double K = 100.0;
    int m = 3;
    double Bup = 120.0;
    double Bdown = 80.0;
    lecture4::DoubleBarrierKI Call =
        lecture4::DoubleBarrierKI(2.3, m, K, Bup, Bdown, true);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 70.0;
    S[2] = 106.0;
    EXPECT_NEAR(Call.Payoff(S), 6.0, 1.0e-8)
        << "Terminal payoff (KI ITM): " << Call.Payoff(S) << std::endl;
    S[1] = 110.0;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
    S[1] = 130.0;
    EXPECT_NEAR(Call.Payoff(S), 6.0, 1.0e-8)
        << "Terminal payoff (KI): " << Call.Payoff(S) << std::endl;
    S[1] = 120.0;
    S[2] = K + 12.73;
    EXPECT_NEAR(Call.Payoff(S), 12.73, 1.0e-8)
        << "Terminal payoff (KI ITM): " << Call.Payoff(S) << std::endl;
    S[2] = K;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (KI ATM): " << Call.Payoff(S) << std::endl;
}

TEST(L4, doubleKIPutPayOffs) {
    double K = 100.0;
    int m = 3;
    double Bup = 120.0;
    double Bdown = 80.0;
    lecture4::DoubleBarrierKI Put =
        lecture4::DoubleBarrierKI(2.3, m, K, Bup, Bdown, false);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 79.99;
    S[2] = 96.0;
    EXPECT_NEAR(Put.Payoff(S), 4.0, 1.0e-8)
        << "Terminal payoff: (KI ITM)" << Put.Payoff(S) << std::endl;
    S[1] = 110.0;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
    S[1] = 120.0;
    EXPECT_NEAR(Put.Payoff(S), 4.0, 1.0e-8)
        << "Terminal payoff: (KI ITM)" << Put.Payoff(S) << std::endl;
    S[1] = 80.0;
    S[2] = K;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (KI ATM): " << Put.Payoff(S) << std::endl;
    S[2] = 126.0;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1.0e-8)
        << "Terminal payoff (KI OTM): " << Put.Payoff(S) << std::endl;
}

// add test for arith asian

double geomMean(lecture4::SamplePath S) {
    double product = 1.0;
    for (double St : S) {
        product *= St;
    }
    return pow(product, 1.0 / (sizeof(S) / sizeof(double)));
}

TEST(L4, geomMean) {
    lecture4::SamplePath S(3);
    S[0] = 100.0;
    S[1] = 70.0;
    S[2] = 106.0;
    double expected = 90.53183053;
    EXPECT_NEAR(geomMean(S), expected, 1.0e-4)
        << "Geom mean = " << geomMean(S) << std::endl;

    S[1] = 160.0;
    expected = 119.2546392;
    EXPECT_NEAR(geomMean(S), expected, 1.0e-4)
        << "Geom mean = " << geomMean(S) << std::endl;
}

TEST(L4, geomAsianCallPayOffs) {
    double K = 100.0;
    int m = 3;
    lecture4::GeomAsian Call = lecture4::GeomAsian(2.3, m, K, true);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 70.0;
    S[2] = 106.0;
    double expected = std::max(geomMean(S) - K, 0.0);
    EXPECT_NEAR(Call.Payoff(S), expected, 1.0e-8)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;

    S[1] = 180.0;
    expected = std::max(geomMean(S) - K, 0.0);
    EXPECT_NEAR(Call.Payoff(S), expected, 1.0e-8)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
}

TEST(L4, geomAsianPutPayOffs) {
    double K = 100.0;
    int m = 3;
    lecture4::GeomAsian Put = lecture4::GeomAsian(2.3, m, K, false);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 70.0;
    S[2] = 106.0;
    double expected = std::max(K - geomMean(S), 0.0);
    EXPECT_NEAR(Put.Payoff(S), expected, 1.0e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;

    S[1] = 180.0;
    expected = std::max(K - geomMean(S), 0.0);
    EXPECT_NEAR(Put.Payoff(S), expected, 1.0e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
}