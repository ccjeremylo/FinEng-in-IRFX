#include <pybind11/pybind11.h>

#include "Lecture1/BinModel01.hpp"
#include "Lecture2/BinModel02.hpp"
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

        .. autosummary::
           :toctree: _generatec
        
           times
           adding
           subtracting

           L1_riskNeutralProb
           L1_NewtonSymb

           L2_BinModel
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
    // Set package version number

    m.attr("__version__") = "0.0.1";
}
