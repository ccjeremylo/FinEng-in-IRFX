#include "BSModel01.hpp"

lecture4::BSModel::BSModel(double S0, double r, double sigma,
                           rng::RNG& generator)
    : S0_(S0), r_(r), sigma_(sigma), generator_(generator){};

// length of S should ideally be deduced automatically
// int m = sizeof(S) / sizeof(double);
lecture4::SamplePath lecture4::BSModel::GenerateSamplePath(double T, int m,
                                                           SamplePath& S) {
    double dt = T / (m - 1);
    double drift = (r_ - 0.5 * sigma_ * sigma_) * dt;
    double terminal_vol = sigma_ * sqrt(dt);
    S[0] = S0_;
    for (int k = 1; k < m; k++) {
        double diff = terminal_vol * generator_.Gauss();
        S[k] = S[k - 1] * exp(drift + diff);
    }
    return S;  // just so we can use it in Python...
}

double lecture4::BSModel::GetR() { return r_; };

double lecture4::BSModel::GetS0() { return S0_; };

double lecture4::BSModel::GetSigma() { return sigma_; };