#pragma once

#include <iostream>
#include <vector>

namespace matrix {

typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;

}  // namespace matrix

matrix::Vector operator*(const matrix::Matrix& M, const matrix::Vector& V);
matrix::Vector operator*(const matrix::Vector& V, const matrix::Vector& W);
matrix::Vector operator*(const double& a, const matrix::Vector& V);

matrix::Vector operator+(const matrix::Vector& V, const matrix::Vector& W);
matrix::Vector operator+(const double& a, const matrix::Vector& V);

matrix::Vector exp(const matrix::Vector& V);
double operator^(const matrix::Vector& V, const matrix::Vector& W);
