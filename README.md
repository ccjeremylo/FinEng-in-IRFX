# Financial Engineering in IRFX in C++

* Following structure of [this course](https://www.city.ac.uk/prospective-students/courses/short-courses/financial-engineering-in-interest-rates-and-fx-cplusplus-applications-in-quantitative-finance). Topics Include:
  - Binomial tree/pricer (function pointers and OO design)
  - American options (using OO features)
  - Monte Carlo methods (exotic payoffs and variance reduction techniques)
  - Non linear solvers for implied vol
  - Curve building
  - Short rate modelling (calibration, bond options, multi-factor HW)
  - HJM (Cheyette model, IR option pricing)
  - LMM (change of numeraire, PCA, stoch vol)
  - SABR
  - etc...
* Contributions are more than welcome!
* The format/set-up of this repo is large based on [another repo](https://github.com/KYLChiu/ExoticMonteCarloEngine/tree/master). Special thanks for [Kelvin](https://github.com/KYLChiu) for letting me copy his set up.

## Features
* Python interface of c++ code using pybind (to be added)
* Gtest
* auto formatting

## Requirements
* CMake 
* C++11 compliant compiler

## Install, Build, and Run
Build:
```
cd {path-to-repo}/FINENG-IN-IRFX/build
cmake ../
make
./exec
```
Run tests:
```
ctest --tests ./build
```

## C++
* The library can be found [here]() - tbd.
* Example tests can be found [here] - tbd.
* Project to-dos are [here] - tbd.


### Lecture 1
Binomial tree option pricing:
* The code can be found [here]() - tbd.

### Lecture 2
Binomial tree option pricing continued:
* pricing american and path-dependent options
* connection to Black Scholes
* The code can be found [here]() - tbd.

### Lecture 3
Monte Carlo pricing:
* pricing american and path-dependent options


