#include "RNGenerator.hpp"

rng::RNG::RNG(int seed)
    : seed_(seed),
      PI_(4.0 * std::atan(1.0)),
      counter_(1){
          // checks that seed > 0
      };

int rng::RNG::GetSeed() { return seed_; };

double rng::RNG::Gauss() { return 0; };

matrix::Vector rng::RNG::GaussVector(int d) {
    matrix::Vector Z(d);
    for (int j = 0; j < d; j++) {
        Z[j] = 0.0;
    }
    return Z;
};

void rng::RNG::incrementSeed() {
    seed_ = seed_ + 1;
    counter_++;
};

rng::BoxMuller::BoxMuller(int seed) : rng::RNG(seed){};

double rng::BoxMuller::Gauss() {
    /* // U1 and U2 are uniform RN: U1, U2 ~ U[0, RAND_MAX]
    std::srand(seed_);
    double U1 = (std::rand() + 1.0) / (RAND_MAX + 1.0);
    double U2 = (std::rand() + 1.0) / (RAND_MAX + 1.0);
    incrementSeed();
    return sqrt(-2.0 * log(U1)) * cos(2.0 * PI_ * U2); */

    // Try to set seed somehow... not clear
    // Generate two random uniform numbers between 0 and 1
    double u1 = static_cast<double>(std::rand()) / RAND_MAX;
    double u2 = static_cast<double>(std::rand()) / RAND_MAX;
    incrementSeed();

    // Box-Muller transform
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return z0;
}

// added as part of lecture 5 - basket options
matrix::Vector rng::BoxMuller::GaussVector(int d) {
    matrix::Vector Z(d);
    for (int j = 0; j < d; j++) {
        Z[j] = Gauss();
    }
    return Z;
}