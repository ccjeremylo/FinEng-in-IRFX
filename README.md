# Financial Engineering in IRFX in C++

Following structure of [this course](https://www.city.ac.uk/prospective-students/courses/short-courses/financial-engineering-in-interest-rates-and-fx-cplusplus-applications-in-quantitative-finance). Topics Include:
* Binomial tree/pricer (function pointers and OO design)
* American options (using OO features)
* Monte Carlo methods (exotic payoffs and variance reduction techniques)
* Non linear solvers for implied vol
* Curve building
* Short rate modelling (calibration, bond options, multi-factor HW)
* HJM (Cheyette model, IR option pricing)
* LMM (change of numeraire, PCA, stoch vol)
* SABR
* etc...

## Features
* Python interface of c++ code using pybind

## Requirements
* CMake (version >= 3.18).
* C++17 compliant compiler.

## Install
Build (generate executable ``````):
```
cd ./build
cmake ..
make
```
Run tests:
```
ctest --test-dir ./build
```

## C++
* The library can be found [here] - tbd.
* Example tests can be found [here] - tbd.
* Project to-dos are [here] - tbd.


### Lecture 1
Binomial tree option pricing:
* The code can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/feature/readme-change/Lecture1/Lecture1).

### Lecture 2
Binomial tree option pricing continued:
* pricing american and path-dependent options
* connection to Black Scholes
* The code can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/feature/readme-change/Lecture2/Lecture2).

### Lecture 3
Monte Carlo pricing:
* pricing american and path-dependent options



