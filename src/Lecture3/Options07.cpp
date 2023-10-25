#include "Options07.hpp"

// European Option
lecture3::EurOption::EurOption(int N) : N_(N) {}

double
    lecture3::EurOption::PriceByCRR(lecture2::BinModel Model) {
    double q = Model.RiskNeutralProb();
    std::vector<double> Price(N_ + 1);
    for (int i = 0; i <= N_; i++) {  // payoff
        Price[i] = Payoff(Model.S(N_, i));
    }
    for (int n = N_ - 1; n >= 0; n--) {  // fill backwards by expectation
        for (int i = 0; i <= n;
             i++) {  // requires double for loop to build entire tree
            Price[i] = ((q * Price[i + 1]) + (1 - q) * (Price[i])) /
                       (1. + Model.GetR());
        }
    }
    return Price[0];
}

// American Option
lecture3::AmOption::AmOption(int N) : N_(N) {}

double
    lecture3::AmOption::PriceBySnell(lecture2::BinModel Model) {
    double q = Model.RiskNeutralProb();
    std::vector<double> Price(N_ + 1);
    double contValue;
    for (int i = 0; i <= N_; i++) {  // payoff
        Price[i] = Payoff(Model.S(N_, i));
    }
    for (int n = N_ - 1; n >= 0; n--) {  // fill backwards by expectation
        for (int i = 0; i <= n;
             i++) {  // requires double for loop to build entire tree
            contValue = ((q * Price[i + 1]) + (1 - q) * (Price[i])) /
                        (1. + Model.GetR());
            Price[i] = Payoff(Model.S(N_, i));
            if (contValue > Price[i]) {
                Price[i] = contValue;
            }
        }
    }
    return Price[0];
}

// Call
lecture3::Call::Call(double K, int N)
    : lecture3::EurOption(N), lecture3::AmOption(N), K_(K){};

double
    lecture3::Call::Payoff(double z) {
    return std::max(z - K_, 0.0);
}

// Call
lecture3::Put::Put(double K, int N)
    : lecture3::EurOption(N), lecture3::AmOption(N), K_(K){};

double
    lecture3::Put::Payoff(double z) {
    return std::max(K_ - z, 0.0);
}