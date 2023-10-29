#include "RNGenerator.hpp"

rng::RNG::RNG(int seed)
    : seed_(seed),
      PI_(4.0 * std::atan(1.0)),
      counter_(1){
          // checks that seed > 0
      };

int rng::RNG::GetSeed() { return seed_; };

double rng::RNG::Gauss() { return 0; };

void rng::RNG::incrementSeed() {
    seed_ = seed_ + 2;
    counter_++;
};

rng::BoxMueller::BoxMueller(int seed) : rng::RNG(seed){};

double rng::BoxMueller::Gauss() {
    srand(seed_);
    double U1 = (std::rand() + 1.0) / (RAND_MAX + 1.0);
    double U2 = (std::rand() + 1.0) / (RAND_MAX + 1.0);

    incrementSeed();
    return sqrt(-2.0 * log(U1)) * cos(2.0 * PI_ * U2);
}