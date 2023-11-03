#include "PathDepOption01.hpp"

#include "../Lecture2/BlackScholes.hpp"
#include "ControlVariate.hpp"

// Base class - m should be property of Model
lecture4::PathDepOption::PathDepOption(double T, int m, bool isCall)
    : T_(T), m_(m), isCall_(isCall){};

double lecture4::PathDepOption::PriceByMC(lecture4::BSModel& Model,
                                          long N) {
    double H = 0.0, Hsq = 0.0;
    SamplePath S(m_);

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

double lecture4::PathDepOption::PriceByControlVariateMC(
    lecture4::BSModel& Model, long N, lecture4::PathDepOption& CVOption) {
    DifferenceOfOptions VarRedOpt(T_, m_, this, &CVOption);

    Price_ =
        VarRedOpt.PriceByMC(Model, N) + CVOption.PriceByFormula(Model);
    PricingError_ = VarRedOpt.PricingError_;
    return Price_;
}

// Arithmetic Asian
lecture4::ArithAsian::ArithAsian(double T, int m, double K, bool isCall)
    : PathDepOption(T, m, isCall), K_(K){};

double lecture4::ArithAsian::Payoff(lecture4::SamplePath& S) {
    double ave = 0.0;
    for (int k = 0; k < m_; k++) {
        ave += S[k];
    }
    ave *= 1.0 / m_;
    if (isCall_) {
        return std::max(ave - K_, 0.0);
    }
    return std::max(K_ - ave, 0.0);
}

// Geometric Asian
lecture4::GeomAsian::GeomAsian(double T, int m, double K, bool isCall)
    : PathDepOption(T, m, isCall), K_(K){};

double lecture4::GeomAsian::Payoff(lecture4::SamplePath& S) {
    double ave = 1.0;
    for (int k = 0; k < m_; k++) {
        ave *= S[k];
    }
    ave = pow(ave, 1.0 / m_);
    if (isCall_) {
        return std::max(ave - K_, 0.0);
    }
    return std::max(K_ - ave, 0.0);
}

// Assumes BS Model
double lecture4::GeomAsian::PriceByFormula(lecture4::BSModel Model) {
    double sig = Model.GetSigma();
    double c1 =
        Model.GetS0() * exp(-0.5 * (Model.GetR() + sig * sig / 6.0) * T_);
    double c2 = sig / sqrt(3.0);
    if (isCall_) {
        return lecture2::call_price(c1, K_, Model.GetR(), c2, T_);
    } else {
        return lecture2::put_price(c1, K_, Model.GetR(), c2, T_);
    }
}

// Vanilla
lecture4::Vanilla::Vanilla(double T, int m, double K, bool isCall)
    : PathDepOption(T, m, isCall), K_(K){};

double lecture4::Vanilla::Payoff(lecture4::SamplePath& S) {
    if (isCall_) {
        return std::max(S[m_ - 1] - K_, 0.0);
    } else {
        return std::max(K_ - S[m_ - 1], 0.0);
    }
}

// Assumes BS Model
double lecture4::Vanilla::PriceByFormula(lecture4::BSModel Model) {
    if (isCall_) {
        return lecture2::call_price(Model.GetS0(), K_, Model.GetR(),
                                    Model.GetSigma(), T_);
    } else {
        return lecture2::put_price(Model.GetS0(), K_, Model.GetR(),
                                   Model.GetSigma(), T_);
    }
}

// Double KO
lecture4::DoubleBarrierKO::DoubleBarrierKO(double T, int m, double K,
                                           double Bup, double Bdown,
                                           bool isCall)
    : PathDepOption(T, m, isCall), K_(K), Bup_(Bup), Bdown_(Bdown){};

double lecture4::DoubleBarrierKO::Payoff(lecture4::SamplePath& S) {
    bool KO = false;
    int k = 0;
    while (KO == false && k < m_) {
        if (S[k] >= Bup_ || S[k] <= Bdown_) {
            KO = true;
        }
        k++;
    }
    if (KO) {
        return 0;
    } else if (isCall_) {
        return std::max(S[m_ - 1] - K_, 0.0);
    } else {
        return std::max(K_ - S[m_ - 1], 0.0);
    }
}

double lecture4::DoubleBarrierKO::PriceByVanillaCVMC(
    lecture4::BSModel& Model, long N, Vanilla& CVOption) {
    return PriceByControlVariateMC(Model, N, CVOption);
}

// Double KI
lecture4::DoubleBarrierKI::DoubleBarrierKI(double T, int m, double K,
                                           double Bup, double Bdown,
                                           bool isCall)
    : PathDepOption(T, m, isCall), K_(K), Bup_(Bup), Bdown_(Bdown){};

double lecture4::DoubleBarrierKI::Payoff(lecture4::SamplePath& S) {
    bool KI = false;
    int k = 0;
    while (KI == false && k < m_) {
        if (S[k] >= Bup_ || S[k] <= Bdown_) {
            KI = true;
        }
        k++;
    }
    if (KI == false) {
        return 0;
    } else if (isCall_) {
        return std::max(S[m_ - 1] - K_, 0.0);
    } else {
        return std::max(K_ - S[m_ - 1], 0.0);
    }
}

// hack for pybind - fix!
// see: https://pybind11.readthedocs.io/en/latest/classes.html
double lecture4::DoubleBarrierKI::PriceByVanillaCVMC(
    lecture4::BSModel& Model, long N, Vanilla& CVOption) {
    return PriceByControlVariateMC(Model, N, CVOption);
}