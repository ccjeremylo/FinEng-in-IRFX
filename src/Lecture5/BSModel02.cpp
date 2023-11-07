#include "BSModel02.hpp"

#include <cmath>
#include <cstdlib>
#include <ctime>

// Pi has been defined in RNG

lecture5::BSModel::BSModel(matrix::Vector S0, double r, matrix::Matrix C,
                           rng::RNG& generator)
    : S0_(S0), r_(r), C_(C), generator_(generator) {
    srand(time(NULL));  // setting seed!
    int d = S0.size();
    sigma_.resize(d);
    for (int j = 0; j < d; j++) {
        // sigma = each row vector of C dot with itself
        sigma_[j] = sqrt(C[j] ^ C[j]);
    }
}

void lecture5::BSModel::GenerateSamplePath(double T, int m,
                                           SamplePath& S) {
    matrix::Vector St = S0_;
    S[0] = St;

    int d = S0_.size();
    double dt = T / (m - 1);
    for (int k = 1; k < m; k++) {
        S[k] = St * exp(dt * (r_ + (-0.5) * sigma_ * sigma_)) +
               sqrt(dt) * (C_ * generator_.GaussVector(d));
        St = S[k];
    }
}

double lecture5::BSModel::GetR() { return r_; }
int lecture5::BSModel::GetDim() { return S0_.size(); }
matrix::Vector lecture5::BSModel::GetS0() { return S0_; }
matrix::Matrix lecture5::BSModel::GetVolMatrix() { return C_; }