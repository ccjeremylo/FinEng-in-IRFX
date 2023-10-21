# Financial Engineering in IRFX in C++

Following structure of [this course](https://www.city.ac.uk/prospective-students/courses/short-courses/financial-engineering-in-interest-rates-and-fx-cplusplus-applications-in-quantitative-finance). <br />

Topics Include:
  - Binomial tree/pricer 
  - American options
  - Monte Carlo methods
  - Non linear solvers for implied vol
  - Curve building
  - Short rate modelling
  - HJM
  - LMM 
  - SABR
  - etc... <br />
  
Contributions are **more** than welcome! <br />

The current format/set-up is largely based on [this repo](https://github.com/KYLChiu/ExoticMonteCarloEngine/tree/master). Special thanks for [Kelvin](https://github.com/KYLChiu) for letting me copy his set up.

## Features
* Python interface of c++ code using ```pybind11``` (see this [readme file](https://github.com/ccjeremylo/FinEng-in-IRFX/blob/main/src/pybind_example/README.md) for more info)
* Unit test suite supported by ```gtest```
* CICD ([to be added](https://github.com/ccjeremylo/FinEng-in-IRFX/issues/15))
* Auto formatting (tbd)

## Requirements
* CMake 
* C++11 compliant compiler

## Install, Build, and Run
### Build:
```
cd {path-to-repo}/FINENG-IN-IRFX/build
cmake ../
make
./exec
```
### Run tests:
```
ctest --tests ./build
```
### Set up & using ```pybind11```:
See this separate [readme file](https://github.com/ccjeremylo/FinEng-in-IRFX/blob/main/src/pybind_example/README.md) for details

## Project Structure
* The library can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/main/src).
* Example tests can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/main/tests).
* Project to-do list are [here](https://github.com/ccjeremylo/FinEng-in-IRFX/issues).


### Lecture 1
* Binomial tree option pricing
  - using function pointers to switch payoffs
  - different choices of tree structure
  - analysing probabililty distribution generated by binomial tree
  - computing Binomial coeff using recurrsion

### Lecture 2
* Binomial tree option pricing continued:
  - improved code design by using objects
  - pricing american and path-dependent options
  - CRR binomial model, numerical and analytical
  - connection to Black Scholes

### Lecture 3
* Monte Carlo pricing:
  - pricing american and path-dependent options
  - using Box-muller as RNG
  - discretisation error in long stepping (terminal correlation)
  - Monte Carlo error analysis and convergence


