#include <pybind11/pybind11.h>
#include "pybind_example/mymath.hpp"
#include "Lecture1/BinModel01.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

PYBIND11_MODULE(cmake_example, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generatec

           add
           subtract
           S
    )pbdoc";

    m.def("times", &mymath_ns::multiply_doubles, R"pbdoc(
        mutiply 2 numbers
    )pbdoc", py::arg("a"), py::arg("b"));

    m.def("adding", &mymath_ns::adding, R"pbdoc(
        Add two integers
    )pbdoc", py::arg("i"), py::arg("j"));

    m.def("subtracting", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two integers
    )pbdoc", py::arg("i"), py::arg("j"));

    m.attr("__version__") = "0.0.1";

}
