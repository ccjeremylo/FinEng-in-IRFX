#include <gtest/gtest.h>

#include "../src/Lecture4/RNGenerator.hpp"
#include "../src/Lecture5/BSModel02.hpp"
#include "../src/Lecture5/Matrix.hpp"
#include "../src/Lecture5/PathDepBasketOptions.hpp"

// ===============================
// Testing Matrix/Vector operations
// ===============================

TEST(L5, vectorAddition) {
    matrix::Vector V = {1.0, 2.0, 3.0};
    matrix::Vector W = {2.0, 4.0, 6.0};

    matrix::Vector expected = {3.0, 6.0, 9.0};
    matrix::Vector Z = V + W;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L5, vectorScalarAddition) {
    matrix::Vector V = {-1.0, -2.0, 3.0};
    matrix::Vector expected = {1.3, 0.3, 5.3};
    matrix::Vector Z = 2.3 + V;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L5, vectorMultiplication) {
    matrix::Vector V = {1.0, 2.0, 3.0};
    matrix::Vector W = {2.0, 4.0, 6.0};

    matrix::Vector expected = {2.0, 8.0, 18.0};
    matrix::Vector Z = V * W;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L5, vectorMatrixMultiplication) {
    matrix::Matrix M = {{1.0, 2.0}, {-3.0, 100.0}};  // two rows
    matrix::Vector V = {2.0, 6.0};                   // collumn vector

    matrix::Vector expected = {14.0, 594.0};
    matrix::Vector Z = M * V;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L5, vectorExponential) {
    matrix::Vector V = {-2.3, 0.0, 2.0, 6.0};
    matrix::Vector Z = exp(V);

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], exp(V[i]), 1e-8);
    }
}

TEST(L5, vectorDotProduct) {
    matrix::Vector V = {-2.3, 0.0};
    matrix::Vector W = {4.0, -1.0};

    int d = V.size();
    EXPECT_NEAR(V ^ W, -9.2, 1e-8);
}

// ===============================
// Testing multi-asset simulation
// ===============================

TEST(L5, multiAssetZeroVolSimulation) {
    rng::BoxMuller BM = rng::BoxMuller(1);

    matrix::Vector S0 = {5.0, 120.0};
    int dim = S0.size();  // number of assets
    double r = 0.03;
    matrix::Matrix C = {S0, S0};  // vol matrix

    int m = 6;  // number of time steps
    lecture5::SamplePath S(m, matrix::Vector(dim, 1));

    // initialising zero vol vol matrix
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            C[i][j] = 0.0;
        }
    }

    EXPECT_TRUE(S.size() == m) << "S.size() = " << S.size()
                               << ", expected (m) = " << m << std::endl;
    for (int t = 0; t < m; t++) {
        EXPECT_TRUE(S[t].size() == dim)
            << "S[t].size() = " << S[t].size()
            << ", expected (dim) = " << dim << std::endl;
    }

    lecture5::BSModel Model(S0, r, C, BM);
    double T = 2.0;
    Model.GenerateSamplePath(T, m, S);

    double dt = T / (m - 1);
    for (int i = 0; i < dim; i++) {
        for (int t = 0; t < m; t++) {
            double S_it = exp(r * t * dt) * S0[i];
            EXPECT_NEAR(S[t][i], S_it, 1e-8)
                << "i:" << i << ", t:" << t << ", S_i(t) = " << S_it
                << std::endl;
        }
    }
}

// ===============================
// Testing Payoffs
// ===============================

TEST(L5, vanillaBasketCallPayOffs) {
    double K = 90.0;
    int m = 3;
    lecture5::VanillaBasket Call(2.3, m, K, true);

    matrix::Vector S0 = {29.0, 10.1, 35.2};
    int dim = S0.size();                    // number of assets
    lecture5::SamplePath S = {S0, S0, S0};  // sample paths

    for (int i = 0; i < dim; i++) {
        S[m - 1][i] = 30.1 + i;
    }
    EXPECT_NEAR(Call.Payoff(S), 3.3, 1e-7)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;

    S[m - 1][0] = 1.1;
    EXPECT_NEAR(Call.Payoff(S), 0.0, 1e-7)
        << "Terminal payoff: " << Call.Payoff(S) << std::endl;
}

TEST(L5, vanillaBasketPutPayOffs) {
    double K = 100.0;
    int m = 8;
    lecture5::VanillaBasket Put(2.3, m, K, false);

    matrix::Vector S0 = {29.0, 10.1, 35.2};
    int dim = S0.size();                                // number of assets
    lecture5::SamplePath S(m, matrix::Vector(dim, 1));  // sample paths

    for (int i = 0; i < dim; i++) {
        S[m - 1][i] = 30.1 + i;
    }
    EXPECT_NEAR(Put.Payoff(S), 6.7, 1e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;

    S[m - 1][0] = 65.1;
    EXPECT_NEAR(Put.Payoff(S), 0.0, 1e-7)
        << "Terminal payoff: " << Put.Payoff(S) << std::endl;
}

// ===============================
// Testing Pricers
// ===============================

TEST(L5, VanillaBasketPricer) {
    rng::BoxMuller BM = rng::BoxMuller(1);

    matrix::Vector S0 = {6.0, 100.0};
    int dim = S0.size();  // number of assets
    double r = 0.02;
    matrix::Matrix C(dim, matrix::Vector(dim, 1));  // vol matrix

    // initialising vol matrix
    C[0][0] = 0.5;
    C[0][1] = -0.3;
    C[1][0] = -0.3;
    C[1][1] = 0.2;

    lecture5::BSModel Model(S0, r, C, BM);

    // option term sheet
    double T = 6.3;
    double ST_0 = S0[0] * exp((r + 0.5 * C[0][0] * C[0][0]) * T);
    double ST_1 = S0[1] * exp((r + 0.5 * C[1][1] * C[1][1]) * T);
    double K = ST_0 + ST_1;

    int m = 30;  // number of time steps
    long PathCount = 1000;

    // Call - Not sure...
    lecture5::VanillaBasket Call(T, m, K, true);
    double MCCallPrice = Call.PriceByMC(Model, PathCount);
    EXPECT_TRUE(MCCallPrice >= 0.0)
        << "Call price: " << MCCallPrice << std::endl;

    // Put - Not sure...
    lecture5::VanillaBasket Put(T, m, K, false);
    double MCPutPrice = Put.PriceByMC(Model, PathCount);
    EXPECT_TRUE(MCPutPrice >= 0.0)
        << "Put price: " << MCPutPrice << std::endl;
}
