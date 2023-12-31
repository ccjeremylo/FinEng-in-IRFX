//
//  BlackScholes.cpp
//  Lecture1
//
//  Created by Jeremy Lo on 10/10/2023.
//
#define _USE_MATH_DEFINES

#include "BlackScholes.hpp"

namespace {
// Standard normal pdf
double norm_pdf(const double& x) {
    return (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x);
}
}  // namespace

// An approximation to the CDF of a standard normal
// Note: This is a recursive function
double lecture1::norm_cdf(const double& x) {
    double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum =
        k *
        (0.319381530 +
         k * (-0.356563782 +
              k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) {
        return (1.0 -
                (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
    } else {
        return 1.0 - norm_cdf(-x);
    }
}

// This calculates d_j, for j in {1,2}
double lecture1::d_j(const int& j, const double& S, const double& K,
                     const double& r, const double& v, const double& T) {
    return (log(S / K) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * T) /
           (v * (pow(T, 0.5)));
}

// Calculate the European vanilla call price
double lecture1::call_price(const double& S, const double& K,
                            const double& r, const double& v,
                            const double& T) {
    return S * lecture1::norm_cdf(lecture1::d_j(1, S, K, r, v, T)) -
           K * exp(-r * T) * lecture1::norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price
double lecture1::put_price(const double& S, const double& K,
                           const double& r, const double& v,
                           const double& T) {
    return -S * lecture1::norm_cdf(-lecture1::d_j(1, S, K, r, v, T)) +
           K * exp(-r * T) * lecture1::norm_cdf(-d_j(2, S, K, r, v, T));
}
