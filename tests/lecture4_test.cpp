#include <gtest/gtest.h>

#include "../src/Lecture2/BlackScholes.hpp"
#include "../src/Lecture4/BSModel01.hpp"
#include "../src/Lecture4/ControlVariate.hpp"
#include "../src/Lecture4/PathDepOption01.hpp"
#include "../src/Lecture4/RNGenerator.hpp"

// ===============================
// Testing Random Number Generators
// ===============================

TEST(L4, BoxMullerSeed) {
    int seed1 = 1;
    int seed2 = 13;

    rng::BoxMuller BM1a = rng::BoxMuller(seed1);
    rng::BoxMuller BM1b = rng::BoxMuller(seed1);
    rng::BoxMuller BM2a = rng::BoxMuller(seed2);
    rng::BoxMuller BM2b = rng::BoxMuller(seed2);

    // EXPECT_EQ(BM1a.GetSeed(), seed1);
    // EXPECT_EQ(BM2a.GetSeed(), seed2);

    double G1a = BM1a.Gauss();
    // EXPECT_EQ(G1a, BM1b.Gauss());
    EXPECT_TRUE(G1a != BM1a.Gauss()) << "N(0,1) =" << G1a << std::endl;

    double G2a = BM2a.Gauss();
    // EXPECT_EQ(G2a, BM2b.Gauss());
    EXPECT_TRUE(G2a != G1a) << G2a << G1a << std::endl;

    // EXPECT_EQ(BM1a.GetSeed(), seed1 + 4);
    // EXPECT_EQ(BM2b.GetSeed(), seed2 + 2);
}

TEST(L4, BoxMuller) {
    int seed = 1;
    rng::BoxMuller BM = rng::BoxMuller(seed);

    double sum = 0.0;
    double squared_sum = 0.0;

    int N = 1000;
    double rand_num = 0.0;
    for (int i = 0; i < N; i++) {
        rand_num = BM.Gauss();
        sum += rand_num;
        squared_sum += rand_num * rand_num;
    }

    double stderr = 1 / sqrt(N);
    double mean = sum / N;
    double variance = (squared_sum - sum * sum) / N;
    EXPECT_NEAR(mean, 0.0, 3 * stderr) << "mean: " << mean;
    // EXPECT_NEAR(variance, 1.0, 3 * stderr) << "variance: " << variance;
}

// ===============================
// Testing Simulation Models
// ===============================

TEST(L4, BSModelZeroVol) {
    rng::BoxMuller BM = rng::BoxMuller(1);

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
        St *= exp(r * T / (m - 1));
    }
}

// ===============================
// Testing Payoffs
// ===============================

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

TEST(L4, differenceOfOptionsPayOffs) {
    double K = 50.0;
    int m = 3;
    double T = 5.0;
    lecture4::ArithAsian AsianCall(T, m, K, true);
    lecture4::Vanilla Call(T, m, K, true);

    lecture4::ArithAsian* AsianCallPtr = &AsianCall;
    lecture4::Vanilla* CallPtr = &Call;

    lecture4::DifferenceOfOptions VarRedOpt(T, m, AsianCallPtr, CallPtr);

    lecture4::SamplePath S(m);
    S[0] = 100.0;
    S[1] = 105.0;
    S[2] = 110.0;

    EXPECT_NEAR(AsianCallPtr->Payoff(S), 105.0 - K, 1.0e-7);
    EXPECT_NEAR(CallPtr->Payoff(S), 110.0 - K, 1.0e-7);
    double expected = AsianCallPtr->Payoff(S) - CallPtr->Payoff(S);
    EXPECT_NEAR(VarRedOpt.Payoff(S), expected, 1.0e-7)
        << "Terminal payoff: " << VarRedOpt.Payoff(S) << std::endl;
}

// ===============================
// Testing Pricers
// ===============================

TEST(L4, VanillaPricer) {
    rng::BoxMuller BM = rng::BoxMuller(1);

    double S0 = 100.0;
    double r = 0.03;
    double sigma = 0.3;
    lecture4::BSModel Model = lecture4::BSModel(S0, r, sigma, BM);

    double K = 80.0;
    int m = 2;
    double T = 6.2;

    int PathCount = 2000;

    // Call
    lecture4::Vanilla Call = lecture4::Vanilla(T, m, K, true);

    double MCCallPrice = Call.PriceByMC(Model, PathCount);
    double BSCallPrice = Call.PriceByFormula(Model);
    double tolerance = std::min(BSCallPrice * 5.0 / sqrt(PathCount), 5.0);
    EXPECT_NEAR(MCCallPrice, BSCallPrice, tolerance)
        << "MC: " << MCCallPrice << ", BS: " << BSCallPrice << std::endl;
    EXPECT_EQ(BM.GetSeed(), 1 + (m - 1) * PathCount)
        << "Seed: " << BM.GetSeed() << std::endl;

    // Put
    lecture4::Vanilla Put = lecture4::Vanilla(T, m, K, false);

    double MCPutPrice = Put.PriceByMC(Model, PathCount);
    double BSPutPrice = Put.PriceByFormula(Model);
    EXPECT_NEAR(MCPutPrice, BSPutPrice, tolerance)
        << "MC: " << MCPutPrice << ", BS: " << BSPutPrice << std::endl;
}

TEST(L4, VanillaAnalyticalPricer) {
    rng::BoxMuller BM = rng::BoxMuller(1);

    double S0 = 100.0;
    double r = 0.05;
    double sigma = 0.3;
    lecture4::BSModel Model = lecture4::BSModel(S0, r, sigma, BM);

    double K = 79.0;
    int m = 3;
    double T = 6.2;

    // Call
    lecture4::Vanilla Call = lecture4::Vanilla(T, m, K, true);
    double CallPrice = Call.PriceByFormula(Model);
    double BSCallPrice = lecture2::call_price(S0, K, r, sigma, T);
    EXPECT_NEAR(CallPrice, BSCallPrice, 1e-7) << "Call";

    // Put
    lecture4::Vanilla Put = lecture4::Vanilla(T, m, K, false);
    double PutPrice = Put.PriceByFormula(Model);
    double BSPutPrice = lecture2::put_price(S0, K, r, sigma, T);
    EXPECT_NEAR(PutPrice, BSPutPrice, 1e-7) << "Put";
}

TEST(L4, ControlVariatePricing) {
    rng::BoxMuller BM = rng::BoxMuller(1);

    double S0 = 100.0;
    double r = 0.01;
    double sigma = 0.15;
    lecture4::BSModel Model = lecture4::BSModel(S0, r, sigma, BM);

    double K = 80.0;
    double T = 5.0;
    int m = 10;

    long N = 1000;

    // Vanilla Call
    lecture4::Vanilla Call = lecture4::Vanilla(T, m, K, true);

    // Geom Asian Call
    lecture4::GeomAsian GeomCall = lecture4::GeomAsian(T, m, K, true);
    double GeomCallPriceCV =
        GeomCall.PriceByControlVariateMC(Model, N, Call);
    double GeomCallErrorCV = GeomCall.GetPricingError();

    double GeomCallPrice = GeomCall.PriceByMC(Model, N);
    double GeomCallError = GeomCall.GetPricingError();

    EXPECT_TRUE(GeomCallErrorCV > 0)
        << ", CVMC error: " << GeomCallErrorCV << std::endl;
    EXPECT_TRUE(GeomCallError > 0)
        << "MC error: " << GeomCallError << std::endl;
    EXPECT_NEAR(GeomCallPriceCV, GeomCallPrice, 5.0 * GeomCallError);
}

// add test for put
TEST(L4, GeometricAsianCallPricing) {
    rng::BoxMuller BM = rng::BoxMuller(1);

    double S0 = 1.0;  // best to normalise this
    double r = 0.03;
    double sigma = 0.13;
    lecture4::BSModel Model = lecture4::BSModel(S0, r, sigma, BM);

    double K = 0.98;
    double T = 5.3;
    int m = 300;  // if m is too big, MC price = inf! Fix!
    // see:
    // https://github.com/ccjeremylo/FinEng-in-IRFX/issues/85

    long N = 1000;

    // Geom Asian Call
    lecture4::GeomAsian GeomCall = lecture4::GeomAsian(T, m, K, true);
    double GeomCallPriceMC = GeomCall.PriceByMC(Model, N);
    double GeomCallPriceError = GeomCall.GetPricingError();

    double GeomCallPrice = GeomCall.PriceByFormula(Model);

    EXPECT_TRUE(GeomCallPrice > 0);
    EXPECT_TRUE(GeomCallPriceMC > 0);
    EXPECT_TRUE(GeomCallPriceError > 0);
    EXPECT_NEAR(GeomCallPriceMC, GeomCallPrice, 5.0 * GeomCallPriceError);
}