// LinearAlgebra.hpp

#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP

#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <vector>

class LinearAlgebra {
   public:
    template <typename T>
    static bool isLinearlyIndependent(std::vector<std::vector<T>> x);

    template <typename T>
    static T determinant(std::vector<std::vector<T>> x, int d);

    template <typename T>
    static T trace(std::vector<std::vector<T>> x);

    template <typename T>
    static T euclideanDistance(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static T norm(std::vector<T> x);

    template <typename T>
    static T norm(std::vector<std::vector<T>> x);

    template <typename T>
    static T norm(std::vector<std::vector<std::vector<T>>> x);

    template <typename T>
    static std::vector<T> add(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static std::vector<std::vector<T>> add(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b);

    template <typename T>
    static std::vector<T> subtract(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static std::vector<std::vector<T>> subtract(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b);

    template <typename T>
    static T dot(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static std::vector<std::vector<T>> matrixMultiply(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b);

    template <typename T>
    static std::vector<T> scalarAdd(std::vector<T> x, T c);

    template <typename T>
    static std::vector<std::vector<T>> scalarAdd(std::vector<std::vector<T>> x, T c);

    template <typename T>
    static std::vector<T> scalarMultiply(std::vector<T> x, T c);

    template <typename T>
    static std::vector<std::vector<T>> scalarMultiply(std::vector<std::vector<T>> x, T c);

    template <typename T>
    static std::vector<T> elementWiseDivision(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static std::vector<std::vector<T>> elementWiseDivision(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b);

    template <typename T>
    static std::vector<T> elementWiseSqrt(std::vector<T> x);

    template <typename T>
    static std::vector<std::vector<T>> elementWiseSqrt(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<T> exp(std::vector<T> x);

    template <typename T>
    static std::vector<std::vector<T>> exp(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<std::vector<T>> matrixPower(std::vector<std::vector<T>> x, int n);

    template <typename T>
    static std::vector<std::vector<T>> gramMatrix(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<std::vector<T>> cofactor(std::vector<std::vector<T>> x, int n, int i, int j);

    template <typename T>
    static std::vector<std::vector<T>> adjoint(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<std::vector<T>> inverse(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<T> hadamardProduct(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static std::vector<std::vector<T>> hadamardProduct(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b);

    template <typename T>
    static std::vector<T> fillVector(int n, T k);

    template <typename T>
    static std::pair<size_t, size_t> get_shape(const std::vector<std::vector<T>> &x);

    template <typename T>
    static std::vector<std::vector<std::vector<T>>> minmax(const std::vector<std::vector<std::vector<T>>> &A, const T &low, const T &high);

    template <typename T>
    static int argmax(const std::vector<std::vector<T>> &A);

    template <typename T>
    static std::vector<std::vector<T>> fillMatrix(const size_t &m, const size_t &n, const T &k);

    template <typename T>
    static std::vector<std::vector<T>> identity(int n);

    template <typename T>
    static std::vector<std::vector<T>> unit_matrix(const size_t &m, const size_t &n);

    template <typename T>
    static std::vector<std::vector<T>> random_matrix(const size_t &m, const size_t &n, const T &low, const T &high);

    template <typename T>
    static std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>> eigen(std::vector<std::vector<T>> x);

    template <typename T>
    static std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>> qrDecomposition(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<std::vector<T>> gramSchmidtProcess(std::vector<std::vector<T>> x);

    template <typename T>
    static std::vector<T> vectorProjection(std::vector<T> a, std::vector<T> b);

    template <typename T>
    static std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>, std::vector<std::vector<T>>> singularValueDecomposition(std::vector<std::vector<T>> x);

    template <typename T>
    static void printMatrix(std::vector<std::vector<T>> x);
};

#endif  // LINEARALGEBRA_HPP