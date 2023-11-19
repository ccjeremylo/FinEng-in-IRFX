# Financial Engineering in IRFX in C++

![Repo Status](https://github.com/ccjeremylo/FinEng-in-IRFX/actions/workflows/cpp-ubuntu.yml/badge.svg?branch=main)

Following structure of [this course](https://www.city.ac.uk/prospective-students/courses/short-courses/financial-engineering-in-interest-rates-and-fx-cplusplus-applications-in-quantitative-finance). <br />

Topics Include:

- Binomial tree/pricer
- American & path-dependent options
- Monte Carlo methods
- Non linear solvers for implied vol
- Curve construction
- Short rate modelling
- HJM
- LMM
- SABR
- etc... <br />
  
Contributions are *more* than welcome! <br />

The current format/set-up is largely based on [this repo](https://github.com/KYLChiu/ExoticMonteCarloEngine/tree/master). Special thanks to [Kelvin](https://github.com/KYLChiu) for letting me copy his set up.

## Features

- Python binding of c++ code via [```pybind11```](https://github.com/pybind/pybind11) (see this [readme file](https://github.com/ccjeremylo/FinEng-in-IRFX/blob/main/src/pybind_example/README.md) for more info)
- Unit test suite supported by [```googletest```](https://github.com/google/googletest)
- CI via [Github Actions](https://github.com/features/actions)
- Code review of jupyter notebooks via [ReviewNB App](https://github.com/apps/review-notebook-app)
- Auto formatting via ```clang-format```

## Requirements

- CMake
- C++11 compliant compiler
- Python3.7 or above
- Gtest

## Install, Build & Run

*All commands* below are assumed to be run from root of the repo, unless specified otherwise.

### Build

```
cmake -S ./ -B build
cmake --build build
./build/exec
```

### Run tests

```
ctest --test-dir ./build --output-on-failure
```

### Build and run tests

The following script only works for linux/macOS users:

```
./build_and_test_proj.sh
```

### Set up & using ```pybind11```

See this separate [readme file](https://github.com/ccjeremylo/FinEng-in-IRFX/blob/main/src/pybind_example/README.md) for details <br />

The following scripts only work for linux/macOS users (and assumes dependencies have been installed) - best to refer to this [readme file](https://github.com/ccjeremylo/FinEng-in-IRFX/blob/main/src/pybind_example/README.md) for set up. <br />

Install our c++ python binding ```fineng_irfx``` into the virtual env ```.venv```:

```
./deploy_cpp_module.sh
```

Now, you can also launch a jupyter lab session with the required virtual env:

```
./launch_jupyter.sh
```

## Project Structure

- The C++ code can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/main/src)
- The Python code can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/main/src/python)
- Example tests can be found [here](https://github.com/ccjeremylo/FinEng-in-IRFX/tree/main/tests)
- Project to-do list are [here](https://github.com/ccjeremylo/FinEng-in-IRFX/issues)

### Lecture 1

- Binomial tree option pricing
  - using [function pointers](https://en.wikipedia.org/wiki/Function_pointer) to switch payoffs
  - different choices of tree structure
  - analysing prob distribution generated by binomial tree
  - computing Binomial coeff using recurrsion

### Lecture 2

- Binomial tree option pricing continued:
  - improve code design by using [OO design patterns](https://refactoring.guru/design-patterns)
  - pricing path-dependent (knock-out) options
  - CRR model, numerical/analytical implementation
  - connection to Black Scholes
  - risks computation via finite differencing

### Lecture 3

- Binomial tree option pricing continued:
  - pricing early excerise payoffs (American/Bermudans)
  - introduction of [C++ templates](https://en.wikipedia.org/wiki/Template_(C%2B%2B))
  - multiple inheritance in C++
  - numerical stability and convergence analysis

- [Monte Carlo methods](https://people.maths.ox.ac.uk/gilesm/mc/):
  - pricing vanilla options
  - using [Box-muller](https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform) as RNG
  - discretisation via the [Euler–Maruyama scheme](https://en.wikipedia.org/wiki/Euler%E2%80%93Maruyama_method)
  - pricing path-dependent payoffs (barrier/Asian)
  - discretisation error in long stepping (terminal correlation)

### Lecture 4

- Monte Carlo methods continued:
  - Monte Carlo error analysis and convergence
  - [variance reduction](https://en.wikipedia.org/wiki/Variance_reduction) techniques
  - pricing arithmetic Asian with geometric asian as [control variate](https://en.wikipedia.org/wiki/Control_variates)
  - pricing barrier with vanilla option as control variate
  - error analysis continued
  - [risks computation & error analysis](https://people.maths.ox.ac.uk/gilesm/mc/module_2/module_2_2.pdf)
 
### Lecture 5

- Monte Carlo methods continued:
  - American Options - [Longstaff-Schwartz method](https://people.maths.ox.ac.uk/gilesm/mc/module_6/american.pdf)
  - multi-asset simulation
  - pricing basket options
 
- 1 factor short rate modelling:
  - introduction to short rate models - 1 factor models
  - [Merton Model](http://www.dl.edi-info.ir/Option%20pricing%20under%20the%20Merton%20model%20of%20the%20short%20rate.pdf) - bond pricing
  - Merton Model - implied yield curve
 
### Lecture 6
 
- 1 factor short rate modelling continued:
  - [Vasicek Model](https://en.wikipedia.org/wiki/Vasicek_model) - bond pricing
  - Vasicek Model - implied yield curve
  - calibration of the Vasicek model to the day-0 yield curve
  - intro to the [Hull White](https://en.wikipedia.org/wiki/Hull%E2%80%93White_model) model
  - calibration of the Hull White model to the day-0 yield curve
