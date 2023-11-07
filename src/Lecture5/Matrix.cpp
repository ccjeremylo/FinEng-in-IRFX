#include "Matrix.hpp"

#include <cmath>

matrix::Vector operator*(const matrix::Matrix& M,
                         const matrix::Vector& V) {
    int d = M.size();  // assumes square matrix
    matrix::Vector W(d);
    for (int j = 0; j < d; j++) {
        W[j] = 0.0;
        for (int i = 0; i < d; i++) {
            W[j] = W[j] + M[j][i] * V[i];
        }
    }
    return W;
}

// element wise multiplication - NOT dot product!
matrix::Vector operator*(const matrix::Vector& V,
                         const matrix::Vector& W) {
    int d = V.size();
    matrix::Vector U(d);
    for (int j = 0; j < d; j++) {
        U[j] = V[j] * W[j];
    }
    return U;
}

matrix::Vector operator*(const double& a, const matrix::Vector& V) {
    int d = V.size();
    matrix::Vector U(d);
    for (int j = 0; j < d; j++) {
        U[j] = a * V[j];
    }
    return U;
}

matrix::Vector operator+(const matrix::Vector& V,
                         const matrix::Vector& W) {
    int d = V.size();
    matrix::Vector U(d);
    for (int j = 0; j < d; j++) {
        U[j] = V[j] + W[j];
    }
    return U;
}

matrix::Vector operator+(const double& a, const matrix::Vector& V) {
    int d = V.size();
    matrix::Vector U(d);
    for (int j = 0; j < d; j++) {
        U[j] = a + V[j];
    }
    return U;
}

matrix::Vector exp(const matrix::Vector& V) {
    int d = V.size();
    matrix::Vector U(d);
    for (int j = 0; j < d; j++) {
        U[j] = exp(V[j]);
    }
    return U;
}

// this IS the dot product!
double operator^(const matrix::Vector& V, const matrix::Vector& W) {
    double sum = 0.0;
    int d = V.size();
    for (int j = 0; j < d; j++) {
        sum += V[j] * W[j];
    }
    return sum;
}