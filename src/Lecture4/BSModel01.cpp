#include "BSModel01.hpp"

lecture4::BSModel::BSModel(double S0, double r, double sigma,
                           rng::RNG generator)
    : S0_(S0), r_(r), sigma_(sigma), generator_(generator){};

// length of S should ideally be deduced automatically
void lecture4::BSModel::GenerateSamplePath(double T, int m,
                                           SamplePath& S) {
    double St = S0_;
    double drift = (r_ - 0.5 * sigma_ * sigma_) * (T / m);
    double vol = sigma_ * sqrt(T / m);
    S[0] = S0_;
    for (int k = 1; k < m; k++) {
        double diff = vol * generator_.Gauss();
        S[k] = S[k - 1] * exp(drift + diff);
    }
}

double lecture4::BSModel::GetR() { return r_; };