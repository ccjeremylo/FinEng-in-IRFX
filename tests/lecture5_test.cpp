#include <gtest/gtest.h>

#include "../src/Lecture5/Matrix.hpp"

// ===============================
// Testing Matrix/Vector operations
// ===============================

TEST(L4, vectorAddition) {
    matrix::Vector V = {1.0, 2.0, 3.0};
    matrix::Vector W = {2.0, 4.0, 6.0};

    matrix::Vector expected = {3.0, 6.0, 9.0};
    matrix::Vector Z = V + W;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L4, vectorScalarAddition) {
    matrix::Vector V = {-1.0, -2.0, 3.0};
    matrix::Vector expected = {1.3, 0.3, 5.3};
    matrix::Vector Z = 2.3 + V;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L4, vectorMultiplication) {
    matrix::Vector V = {1.0, 2.0, 3.0};
    matrix::Vector W = {2.0, 4.0, 6.0};

    matrix::Vector expected = {2.0, 8.0, 18.0};
    matrix::Vector Z = V * W;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L4, vectorMatrixMultiplication) {
    matrix::Matrix M = {{1.0, 2.0}, {-3.0, 100.0}};  // two rows
    matrix::Vector V = {2.0, 6.0};                   // collumn vector

    matrix::Vector expected = {14.0, 594.0};
    matrix::Vector Z = M * V;

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], expected[i], 1e-8);
    }
}

TEST(L4, vectorExponential) {
    matrix::Vector V = {-2.3, 0.0, 2.0, 6.0};
    matrix::Vector Z = exp(V);

    int d = V.size();
    for (int i = 0; i < d; i++) {
        EXPECT_NEAR(Z[i], exp(V[i]), 1e-8);
    }
}

TEST(L4, vectorDotProduct) {
    matrix::Vector V = {-2.3, 0.0};
    matrix::Vector W = {4.0, -1.0};

    int d = V.size();
    EXPECT_NEAR(V ^ W, -9.2, 1e-8);
}