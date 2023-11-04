#include "BSModel01.hpp"
#include "PathDepOption01.hpp"

namespace lecture4 {

class DifferenceOfOptions : public lecture4::PathDepOption {
public:
    DifferenceOfOptions(double T, int m, PathDepOption* Ptr1,
                        PathDepOption* Ptr2);
    double Payoff(lecture4::SamplePath& S);

protected:
    double T_;
    int m_;
    PathDepOption* Ptr1_;  // should we use smart ptr?
    PathDepOption* Ptr2_;
};

}  // namespace lecture4