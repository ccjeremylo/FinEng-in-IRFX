#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Lecture1/BinModel01.hpp"
#include "Lecture2/BinModel02.hpp"
#include "Lecture3/Options07.hpp"
#include "Lecture4/BSModel01.hpp"
#include "Lecture4/PathDepOption01.hpp"
#include "Lecture4/RNGenerator.hpp"
#include "pybind_example/mymath.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

// at the moment, just going to manually add new functions/classes here
// there might be a smarter way to do this...?
PYBIND11_MODULE(fineng_irfx, m) {
    m.doc() = R"pbdoc(
        Pybind11 plugin
        -----------------------
        .. currentmodule:: fineng_irfx
    )pbdoc";

    // -----------------
    // Toy examples

    m.def("times", &mymath_ns::multiply_doubles, R"pbdoc(
        mutiply 2 numbers
    )pbdoc",
          py::arg("a"), py::arg("b"));

    m.def("adding", &mymath_ns::adding, R"pbdoc(
        Add two integers
    )pbdoc",
          py::arg("i"), py::arg("j"));

    m.def(
        "subtracting", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two integers
    )pbdoc",
        py::arg("i"), py::arg("j"));

    // -----------------
    // Lecture 1

    m.def("L1_riskNeutralProb", &lecture1::riskNeutralProb, R"pbdoc(
        Compute risk neutral prob for up move in Binomial model
    )pbdoc",
          py::arg("U"), py::arg("D"), py::arg("R"));

    m.def("L1_NewtonSymb", &lecture1::NewtonSymb, R"pbdoc(
        Compute Binomial coeff
    )pbdoc",
          py::arg("N"), py::arg("i"));

    m.def("L1_S", &lecture1::S, R"pbdoc(
        Generate stock tree
    )pbdoc",
          py::arg("S0"), py::arg("U"), py::arg("D"), py::arg("n"),
          py::arg("i"));

    // -----------------
    // Lecture 2

    py::class_<lecture2::BinModel>(m, "L2_BinModel")
        .def(py::init<double, double, double, double>())
        .def("RiskNeutralProb", &lecture2::BinModel::RiskNeutralProb)
        .def("S", &lecture2::BinModel::S)
        .def_property_readonly("GetR", &lecture2::BinModel::GetR);

    // -----------------
    // Lecture 3

    py::class_<lecture3::Call>(m, "L3_Call")
        .def(py::init<double, int>())
        .def("Payoff", &lecture3::Call::Payoff)
        .def("PriceByCRR", &lecture3::Call::PriceByCRR)
        .def("PriceBySnell", &lecture3::Call::PriceBySnell);

    py::class_<lecture3::Put>(m, "L3_Put")
        .def(py::init<double, int>())
        .def("Payoff", &lecture3::Put::Payoff)
        .def("PriceByCRR", &lecture3::Put::PriceByCRR)
        .def("PriceBySnell", &lecture3::Put::PriceBySnell);

    // -----------------
    // Lecture 4

    py::class_<rng::BoxMuller>(m, "L4_BoxMuller")
        .def(py::init<int>())
        .def("Gauss", &rng::BoxMuller::Gauss)
        .def_property_readonly("GetSeed", &rng::BoxMuller::GetSeed);

    py::class_<lecture4::SamplePath>(m, "L4_SamplePath")
        .def(py::init<int>());

    py::class_<lecture4::BSModel>(m, "L4_BSModel")
        .def(py::init<double, double, double, rng::BoxMuller&>())  // fix?
        .def("GenerateSamplePath", &lecture4::BSModel::GenerateSamplePath)
        .def_property_readonly("GetR", &lecture4::BSModel::GetR)
        .def_property_readonly("GetS0", &lecture4::BSModel::GetS0)
        .def_property_readonly("GetSigma", &lecture4::BSModel::GetSigma);

    py::class_<lecture4::ArithAsian>(m, "L4_ArithAsian")
        .def(py::init<double, int, double, bool>())
        .def("PriceByMC", &lecture4::ArithAsian::PriceByMC)
        .def("PriceByCVMC", &lecture4::ArithAsian::PriceByControlVariateMC)
        .def("Payoff", &lecture4::ArithAsian::Payoff)
        .def_property_readonly("GetPrice", &lecture4::ArithAsian::GetPrice)
        .def_property_readonly("GetPricingError",
                               &lecture4::ArithAsian::GetPricingError);

    py::class_<lecture4::GeomAsian>(m, "L4_GeomAsian")
        .def(py::init<double, int, double, bool>())
        .def("PriceByMC", &lecture4::GeomAsian::PriceByMC)
        .def("PriceByCVMC", &lecture4::GeomAsian::PriceByControlVariateMC)
        .def("Payoff", &lecture4::GeomAsian::Payoff)
        .def_property_readonly("GetPrice", &lecture4::GeomAsian::GetPrice)
        .def_property_readonly("GetPricingError",
                               &lecture4::GeomAsian::GetPricingError);

    py::class_<lecture4::Vanilla>(m, "L4_Vanilla")
        .def(py::init<double, int, double, bool>())
        .def("PriceByMC", &lecture4::Vanilla::PriceByMC)
        .def("PriceByFormula", &lecture4::Vanilla::PriceByFormula)
        .def("Payoff", &lecture4::Vanilla::Payoff)
        .def_property_readonly("GetPrice", &lecture4::Vanilla::GetPrice)
        .def_property_readonly("GetPricingError",
                               &lecture4::Vanilla::GetPricingError);

    py::class_<lecture4::DoubleBarrierKO>(m, "L4_DoubleBarrierKO")
        .def(py::init<double, int, double, double, double, bool>())
        .def("PriceByMC", &lecture4::DoubleBarrierKO::PriceByMC)
        .def("PriceByCVMC",
             &lecture4::DoubleBarrierKO::PriceByControlVariateMC)
        .def("PriceByVanillaCVMC",
             &lecture4::DoubleBarrierKO::PriceByVanillaCVMC)
        .def("Payoff", &lecture4::DoubleBarrierKO::Payoff)
        .def_property_readonly("GetPrice",
                               &lecture4::DoubleBarrierKO::GetPrice)
        .def_property_readonly(
            "GetPricingError",
            &lecture4::DoubleBarrierKO::GetPricingError);

    py::class_<lecture4::DoubleBarrierKI>(m, "L4_DoubleBarrierKI")
        .def(py::init<double, int, double, double, double, bool>())
        .def("PriceByMC", &lecture4::DoubleBarrierKI::PriceByMC)
        .def("PriceByCVMC",
             &lecture4::DoubleBarrierKI::PriceByControlVariateMC)
        .def("PriceByVanillaCVMC",
             &lecture4::DoubleBarrierKI::PriceByVanillaCVMC)
        .def("Payoff", &lecture4::DoubleBarrierKI::Payoff)
        .def_property_readonly("GetPrice",
                               &lecture4::DoubleBarrierKI::GetPrice)
        .def_property_readonly(
            "GetPricingError",
            &lecture4::DoubleBarrierKI::GetPricingError);

    // -----------------
    // Lecture 5

    // -----------------
    // Set package version number

    m.attr("__version__") = "0.0.1";
}
