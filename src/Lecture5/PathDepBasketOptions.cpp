#include "PathDepBasketOptions.hpp"

// Base class - m should be property of Model
lecture5::PathDepBasketOption::PathDepBasketOption(double T, int m,
                                                   bool isCall)
    : T_(T), m_(m), isCall_(isCall){};

double lecture5::PathDepBasketOption::PriceByMC(lecture5::BSModel& Model,
                                                long N) {
    double H = 0.0, Hsq = 0.0;
    SamplePath S(m_, matrix::Vector(Model.GetDim(), 1));

    for (long i = 0; i < N; i++) {
        Model.GenerateSamplePath(T_, m_, S);
        H = (i * H + Payoff(S)) / (i + 1.0);
        Hsq = (i * Hsq + pow(Payoff(S), 2.0)) / (i + 1.0);
    }
    double DF = exp(-Model.GetR() * T_);
    Price_ = DF * H;
    PricingError_ = DF * sqrt(Hsq - H * H) / sqrt(N - 1.0);
    return Price_;
}

lecture5::VanillaBasket::VanillaBasket(double T, int m, double K,
                                       bool isCall)
    : PathDepBasketOption(T, m, isCall), K_(K){};

double lecture5::VanillaBasket::Payoff(lecture5::SamplePath& S) {
    double sum = 0.0;
    int dim = S[0].size();
    for (int i = 0; i < dim; i++) {
        sum += S[m_ - 1][i];
    }
    if (isCall_) {
        return std::max(sum - K_, 0.0);
    } else {
        return std::max(K_ - sum, 0.0);
    }
}