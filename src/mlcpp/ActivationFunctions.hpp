// ActivationFunctions.hpp

#ifndef ACTIVATIONFUNCTIONS_HPP
#define ACTIVATIONFUNCTIONS_HPP

#include <algorithm>
#include <cmath>
#include <vector>

#include "LinearAlgebra.hpp"

class ActivationFunctions {
   public:
    template <typename T>
    static T identity(const T &x, const bool &derivative);
    template <typename T>
    static std::vector<T> identity(const std::vector<T> &x, const bool &derivative);
    template <typename T>
    static std::vector<std::vector<T>> identity(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T linear(const T &x, const bool &derivative);
    template <typename T>
    static std::vector<T> linear(const std::vector<T> &x, const bool &derivative);
    template <typename T>
    static std::vector<std::vector<T>> linear(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T sigmoid(const T &x, const bool &derivative);

    template <typename T>
    static std::vector<T> sigmoid(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> sigmoid(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static std::vector<T> softmax(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> softmax(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T RELU(const T &x, const bool &derivative);

    template <typename T>
    static std::vector<T> RELU(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> RELU(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T leakyRELU(const T &x, const T &c, const bool &derivative);

    template <typename T>
    static std::vector<T> leakyRELU(const std::vector<T> &x, const double &c, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> leakyRELU(const std::vector<std::vector<T>> &x, const T &c, const bool &derivative);

    template <typename T>
    static T ELU(const T &x, const T &c, const bool &derivative);

    template <typename T>
    static std::vector<T> ELU(const std::vector<T> &x, const T &c, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> ELU(const std::vector<std::vector<double>> &x, const double &c, const bool &derivative);

    template <typename T>
    static T PRELU(const T &x, const T &c, const bool &derivative);

    template <typename T>
    static std::vector<T> PRELU(const std::vector<T> &x, const T &c, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> PRELU(const std::vector<std::vector<T>> &x, const T &c, const bool &derivative);

    template <typename T>
    static T sinh(const T &x, const bool &derivative);

    template <typename T>
    static std::vector<T> sinh(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> sinh(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T cosh(const T &x, const bool &derivative);

    template <typename T>
    static std::vector<T> cosh(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> cosh(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T tanh(const T &x, const bool &derivative);

    template <typename T>
    static std::vector<T> tanh(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> tanh(const std::vector<std::vector<T>> &x, const bool &derivative);

    template <typename T>
    static T swish(const T &x, const bool &derivative);

    template <typename T>
    static std::vector<T> swish(const std::vector<T> &x, const bool &derivative);

    template <typename T>
    static std::vector<std::vector<T>> swish(const std::vector<std::vector<T>> &x, const bool &derivative);
};

#endif  // ACTIVATIONFUNCTIONS_HPP