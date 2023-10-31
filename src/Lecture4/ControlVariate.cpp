#include "ControlVariate.hpp"

lecture4::DifferenceOfOptions::DifferenceOfOptions(double T, int m,
                                                   PathDepOption* Ptr1,
                                                   PathDepOption* Ptr2)
    : PathDepOption(T, m, true), Ptr1_(Ptr1), Ptr2_(Ptr2){};

double lecture4::DifferenceOfOptions::Payoff(lecture4::SamplePath& S) {
    return Ptr1_->Payoff(S) - Ptr2_->Payoff(S);
}
