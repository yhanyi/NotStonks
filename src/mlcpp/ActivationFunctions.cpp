#include "ActivationFunctions.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

#include "LinearAlgebra.hpp"

template <typename T>
T ActivationFunctions::identity(const T &x, const bool &derivative) { return x; }
template <typename T>
std::vector<T> ActivationFunctions::identity(const std::vector<T> &x, const bool &derivative) { return x; }
template <typename T>
std::vector<std::vector<T>> ActivationFunctions::identity(const std::vector<std::vector<T>> &x, const bool &derivative) { return x; }

template <typename T>
T ActivationFunctions::linear(const T &x, const bool &derivative) { return derivative ? 1 : x; }
template <typename T>
std::vector<T> ActivationFunctions::linear(const std::vector<T> &x, const bool &derivative) { return derivative ? LinearAlgebra::fillVector(x.size(), 1) : x; }
template <typename T>
std::vector<std::vector<T>> ActivationFunctions::linear(const std::vector<std::vector<T>> &x, const bool &derivative) { return derivative ? LinearAlgebra::fillMatrix(x.size(), x[0].size(), 1) : x; }

template <typename T>
T ActivationFunctions::sigmoid(const T &x, const bool &derivative) {
    return derivative ? ActivationFunctions::sigmoid(x, 0) * (1 - ActivationFunctions::sigmoid(x, 0)) : 1 / (1 + exp(-x));
}

template <typename T>
std::vector<T> ActivationFunctions::sigmoid(const std::vector<T> &x, const bool &derivative) {
    if (derivative) return LinearAlgebra::subtract(sigmoid(x), LinearAlgebra::hadamardProduct(sigmoid(x), sigmoid(x)));
    return LinearAlgebra::elementWiseDivision(LinearAlgebra::fillVector(x.size(), 1), LinearAlgebra::add(LinearAlgebra::fillVector(x.size(), 1), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))));
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::sigmoid(const std::vector<std::vector<T>> &x, const bool &derivative) {
    if (derivative) return LinearAlgebra::subtract(sigmoid(x), LinearAlgebra::hadamardProduct(sigmoid(x), sigmoid(x)));
    return LinearAlgebra::elementWiseDivision(LinearAlgebra::fillMatrix(x.size(), x[0].size(), 1), LinearAlgebra::add(LinearAlgebra::fillMatrix(x.size(), x[0].size(), 1), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))));
}

template <typename T>
std::vector<T> ActivationFunctions::softmax(const std::vector<T> &x, const bool &derivative) {
    std::vector<T> vec(x.size());
    std::vector<T> e = LinearAlgebra::exp(x);
    T total = 0.0;
    for (int i = 0; i < x.size(); i++) {
        total += x[i];
    }
    for (int i = 0; i < x.size(); i++) {
        vec[i] = e[i] / total;
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::softmax(const std::vector<std::vector<T>> &x, const bool &derivative) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = ActivationFunctions::softmax(x[i]);
    }
    return matrix;
}

template <typename T>
T ActivationFunctions::RELU(const T &x, const bool &derivative) {
    if (derivative) return (x <= 0) ? 0 : 1;
    return fmax(0, x);
}

template <typename T>
std::vector<T> ActivationFunctions::RELU(const std::vector<T> &x, const bool &derivative) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = ActivationFunctions::RELU(x[i], derivative);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::RELU(const std::vector<std::vector<T>> &x, const bool &derivative) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = ActivationFunctions::RELU(x[i], derivative);
    }
    return matrix;
}

template <typename T>
T ActivationFunctions::leakyRELU(const T &x, const T &c, const bool &derivative) {
    if (derivative) return (x <= 0) ? c : 1;
    return fmax(c * x, x);
}

template <typename T>
std::vector<T> ActivationFunctions::leakyRELU(const std::vector<T> &x, const double &c, const bool &derivative) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = ActivationFunctions::leakyRELU(x[i], derivative);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::leakyRELU(const std::vector<std::vector<T>> &x, const T &c, const bool &derivative) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = ActivationFunctions::leakyRELU(x[i], derivative);
    }
    return matrix;
}

template <typename T>
T ActivationFunctions::ELU(const T &x, const T &c, const bool &derivative) {
    if (derivative) return (x <= 0) ? c * std::exp(x) : 1;
    return (x <= 0) ? c * (std::exp(x) - 1) : x;
}

template <typename T>
std::vector<T> ActivationFunctions::ELU(const std::vector<T> &x, const T &c, const bool &derivative) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = ActivationFunctions::ELU(x[i], c, derivative);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::ELU(const std::vector<std::vector<double>> &x, const double &c, const bool &derivative) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = ActivationFunctions::ELU(x[i], c, derivative);
    }
    return matrix;
}

template <typename T>
T ActivationFunctions::PRELU(const T &x, const T &c, const bool &derivative) {
    if (derivative) return (x <= 0) ? c : 1;
    return (x <= 0) ? c * x : x;
}

template <typename T>
std::vector<T> ActivationFunctions::PRELU(const std::vector<T> &x, const T &c, const bool &derivative) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = PRELU(x[i], c, derivative);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::PRELU(const std::vector<std::vector<T>> &x, const T &c, const bool &derivative) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = PRELU(x[i], c, derivative);
    }
    return matrix;
}

template <typename T>
T ActivationFunctions::sinh(const T &x, const bool &derivative) {
    return derivative ? std::cosh(x) : 0.5 * (exp(x) - exp(-x));
}

template <typename T>
std::vector<T> ActivationFunctions::sinh(const std::vector<T> &x, const bool &derivative) {
    return derivative ? cosh(x) : LinearAlgebra::scalarMultiply(LinearAlgebra::subtract(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))), 0.5);
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::sinh(const std::vector<std::vector<T>> &x, const bool &derivative) {
    return derivative ? cosh(x) : LinearAlgebra::scalarMultiply(LinearAlgebra::subtract(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))), 0.5);
}

template <typename T>
T ActivationFunctions::cosh(const T &x, const bool &derivative) {
    return derivative ? std::sinh(x) : 0.5 * (exp(x) + exp(-x));
}

template <typename T>
std::vector<T> ActivationFunctions::cosh(const std::vector<T> &x, const bool &derivative) {
    return derivative ? sinh(x) : LinearAlgebra::scalarMultiply(LinearAlgebra::add(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))), 0.5);
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::cosh(const std::vector<std::vector<T>> &x, const bool &derivative) {
    return derivative ? sinh(x) : LinearAlgebra::scalarMultiply(LinearAlgebra::add(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))), 0.5);
}

template <typename T>
T ActivationFunctions::tanh(const T &x, const bool &derivative) {
    return derivative ? (1 - std::tanh(x) * std::tanh(x)) : (exp(x) - exp(-x)) / (exp(x) + exp(x));
}

template <typename T>
std::vector<T> ActivationFunctions::tanh(const std::vector<T> &x, const bool &derivative) {
    if (derivative)
        return LinearAlgebra::scalarMultiply(LinearAlgebra::scalarAdd(LinearAlgebra::hadamardProduct(tanh(x), tanh(x)), -1), -1);
    else
        return LinearAlgebra::elementWiseDivision(LinearAlgebra::subtract(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))), LinearAlgebra::add(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))));
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::tanh(const std::vector<std::vector<T>> &x, const bool &derivative) {
    if (derivative)
        return LinearAlgebra::scalarMultiply(LinearAlgebra::scalarAdd(LinearAlgebra::hadamardProduct(tanh(x), tanh(x)), -1), -1);
    else
        return LinearAlgebra::elementWiseDivision(LinearAlgebra::subtract(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))), LinearAlgebra::add(LinearAlgebra::exp(x), LinearAlgebra::exp(LinearAlgebra::scalarMultiply(x, -1))));
}

template <typename T>
T ActivationFunctions::swish(const T &x, const bool &derivative) {
    return derivative ? swish(x) + (x / (1 + std::exp(-x))) * (1 - swish(x)) : x / (1 + std::exp(-x));
}

template <typename T>
std::vector<T> ActivationFunctions::swish(const std::vector<T> &x, const bool &derivative) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = swish(x[i], derivative);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> ActivationFunctions::swish(const std::vector<std::vector<T>> &x, const bool &derivative) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = swish(x[i], derivative);
    }
    return matrix;
}