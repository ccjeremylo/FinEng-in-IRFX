#include <gtest/gtest.h>

#include "../src/Lecture4/BSModel01.hpp"
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
