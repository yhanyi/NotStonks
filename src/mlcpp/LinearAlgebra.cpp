#include "LinearAlgebra.hpp"

#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <vector>

template <typename T>
bool LinearAlgebra::isLinearlyIndependent(std::vector<std::vector<T>> x) {
    return (determinant(gramMatrix(x), x.size()) == 0);
}

template <typename T>
T LinearAlgebra::determinant(std::vector<std::vector<T>> x, int d) {
    if (d == 2) {
        return x[0][0] * x[1][1] - x[0][1] * x[1][0];
    }
    T det = 0;
    std::vector<std::vector<T>> sub(d, std::vector<T>(d));
    for (int i = 0; i < d; i++) {
        int ii = 0;
        for (int j = 1; j < d; j++) {
            int jj = 0;
            for (int k = 0; k < d; k++) {
                if (k == i) continue;
                sub[ii][jj] = x[j][k];
                jj++;
            }
            ii++;
        }
        det += std::pow(-1, i) * x[0][i] * determinant(sub, d - 1);
    }
    return det;
}

template <typename T>
T LinearAlgebra::trace(std::vector<std::vector<T>> x) {
    T trace = 0;
    for (int i = 0; i < x.size(); i++) {
        trace += x[i][i];
    }
    return trace;
}

template <typename T>
T LinearAlgebra::euclideanDistance(std::vector<T> a, std::vector<T> b) {
    T total = 0;
    for (int i = 0; i < a.size(); i++) {
        total += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(total);
}

template <typename T>
T LinearAlgebra::norm(std::vector<T> x) {
    T total = 0.0;
    for (int i = 0; i < x.size(); i++) {
        total += x[i] * x[i];
    }
    return std::sqrt(total);
}

template <typename T>
T LinearAlgebra::norm(std::vector<std::vector<T>> x) {
    T total = 0.0;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            total += x[i][j] * x[i][j];
        }
    }
    return std::sqrt(total);
}

template <typename T>
T LinearAlgebra::norm(std::vector<std::vector<std::vector<T>>> x) {
    T total = 0.0;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            for (int k = 0; k < x[0][0].size(); k++) {
                total += x[i][j][k] * x[i][j][k];
            }
        }
    }
    return std::sqrt(total);
}

template <typename T>
std::vector<T> add(std::vector<T> a, std::vector<T> b) {
    std::vector<T> vec(a.size());
    for (int i = 0; i < a.size(); i++) {
        vec[i] = a[i] + b[i];
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> add(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b) {
    std::vector<std::vector<T>> matrix;
    int m = a[0].size(), n = a.size();
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);
        for (int j = 0; j < m; j++) {
            matrix[i][j] = a[i][j] + b[i][j];
        }
    }
    return matrix;
}

template <typename T>
std::vector<T> subtract(std::vector<T> a, std::vector<T> b) {
    std::vector<T> vec(a.size());
    for (int i = 0; i < a.size(); i++) {
        vec[i] = a[i] - b[i];
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> subtract(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b) {
    std::vector<std::vector<T>> matrix;
    int m = a[0].size(), n = a.size();
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);
        for (int j = 0; j < m; j++) {
            matrix[i][j] = a[i][j] - b[i][j];
        }
    }
    return matrix;
}

template <typename T>
T dot(std::vector<T> a, std::vector<T> b) {
    T total = 0.0;
    for (int i = 0; i < a.size(); i++) {
        total += a[i] * b[i];
    }
    return total;
}

template <typename T>
std::vector<std::vector<T>> matrixMultiply(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b) {
    std::vector<std::vector<T>> matrix(a.size(), std::vector<T>(b[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                matrix[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return matrix;
}

template <typename T>
std::vector<T> scalarAdd(std::vector<T> x, T c) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = x[i] + c;
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> scalarAdd(std::vector<std::vector<T>> x, T c) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            matrix[i][j] = x[i][j] + c;
        }
    }
    return x;
}

template <typename T>
std::vector<T> scalarMultiply(std::vector<T> x, T c) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = x[i] * c;
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> scalarMultiply(std::vector<std::vector<T>> x, T c) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            matrix[i][j] = x[i][j] * c;
        }
    }
    return x;
}

template <typename T>
std::vector<T> elementWiseDivision(std::vector<T> a, std::vector<T> b) {
    std::vector<T> vec(a.size());
    for (int i = 0; i < a.size(); i++) {
        vec[i] = a[i] / b[i];
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> elementWiseDivision(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b) {
    std::vector<std::vector<T>> matrix(a.size(), std::vector<T>(a[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            matrix[i][j] = a[i][j] / b[i][j];
        }
    }
    return matrix;
}

template <typename T>
std::vector<T> elementWiseSqrt(std::vector<T> x) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = sqrt(x[i]);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> elementWiseSqrt(std::vector<std::vector<T>> x) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        matrix[i] = elementWiseSqrt(x[i]);
    }
    return matrix;
}

template <typename T>
std::vector<T> exp(std::vector<T> x) {
    std::vector<T> vec(x.size());
    for (int i = 0; i < x.size(); i++) {
        vec[i] = std::exp(x[i]);
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> exp(std::vector<std::vector<T>> x) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            matrix[i][j] = std::exp(x[i][j]);
        }
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> x) {
    std::vector<std::vector<T>> matrix(x[0].size(), std::vector<T>(x.size()));
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            matrix[j][i] = x[i][j];
        }
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> matrixPower(std::vector<std::vector<T>> x, int n) {
    std::vector<std::vector<T>> matrix = identity(x.size());
    if (n == 0)
        return matrix;
    else if (n < 0)
        x = inverse(x);
    for (int i = 0; i < std::abs(n); i++) {
        matrix = matrixMultiply(matrix, x);
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> gramMatrix(std::vector<std::vector<T>> x) {
    return matrixMultiply(transpose(x), x);
}

template <typename T>
std::vector<std::vector<T>> cofactor(std::vector<std::vector<T>> x, int n, int i, int j) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x.size()));
    int ii = 0, jj = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != i && col != j) {
                matrix[ii][jj++] = x[row][col];
                if (jj == n - 1) {
                    jj = 0;
                    i++;
                }
            }
        }
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> adjoint(std::vector<std::vector<T>> x) {
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x.size()));
    if (x.size() == 1) {
        matrix[0][0] = 1;
        return matrix;
    }
    if (x.size() == 2) {
        matrix[0][0] = x[1][1];
        matrix[1][1] = x[0][0];
        matrix[0][1] = -x[0][1];
        matrix[1][0] = -x[1][0];
        return matrix;
    }
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x.size(); j++) {
            std::vector<std::vector<T>> c = cofactor(x, int(x.size()), i, j);
            int sign = ((i + j) % 2) ? -1 : 1;
            matrix[j][i] = sign * determinant(c, x.size() - 1);
        }
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> inverse(std::vector<std::vector<T>> x) {
    return scalarMultiply(adjoint(x), 1 / determinant(x, x.size()));
}

template <typename T>
std::vector<T> hadamardProduct(std::vector<T> a, std::vector<T> b) {
    std::vector<T> vec(a.size());
    for (int i = 0; i < a.size(); i++) {
        vec[i] = a[i] * b[i];
    }
    return vec;
}

template <typename T>
std::vector<std::vector<T>> hadamardProduct(std::vector<std::vector<T>> a, std::vector<std::vector<T>> b) {
    std::vector<std::vector<T>> matrix(a.size(), std::vector<T>(a[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            matrix[i][j] = a[i][j] * b[i][j];
        }
    }
    return matrix;
}

template <typename T>
std::vector<T> fillVector(int n, T k) {
    std::vector<T> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i] = k;
    }
    return vec;
}

template <typename T>
std::pair<size_t, size_t> get_shape(const std::vector<std::vector<T>> &x) {
    return {x.size(), x[0].size()};
}

template <typename T>
std::vector<std::vector<std::vector<T>>> minmax(
    const std::vector<std::vector<std::vector<T>>> &A, const T &low, const T &high) {
    std::vector<std::vector<std::vector<T>>> B = A;
    const auto shape = get_shape(B[0]);
    if (shape.first != 1) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr
            << "Supplied vector is not supported for minmax scaling, shape: ";
        std::cerr << "(" << shape.first << ", " << shape.second << ")" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < shape.second; i++) {
        T min = B[0][0][i], max = B[0][0][i];
        for (int j = 0; j < B.size(); j++) {
            min = std::min(min, B[j][0][i]);
            max = std::max(max, B[j][0][i]);
        }
        for (int j = 0; j < B.size(); j++) {
            B[j][0][i] = ((B[j][0][i] - min) / (max - min)) * (high - low) + low;
        }
    }
    return B;
}

template <typename T>
int argmax(const std::vector<std::vector<T>> &A) {
    const auto shape = get_shape(A);
    if (shape.first != 1) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Supplied vector is not supported for argmax" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return std::distance(std::begin(A[0]), std::max_element(std::begin(A[0]), std::end(A[0])));
}

template <typename T>
std::vector<std::vector<T>> fillMatrix(const size_t &m, const size_t &n, const T &k) {
    std::vector<std::vector<T>> matrix(n, std::vector<T>(m));
    matrix.resize(n);
    for (int i = 0; i < n; i++) {
        matrix.resize(m);
        for (int j = 0; j < m; j++) {
            matrix[i][j] = k;
        }
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> identity(int n) {
    std::vector<std::vector<T>> matrix(n, std::vector<T>(n));
    matrix = fillMatrix(n, n, 0);
    for (int i = 0; i < n; i++) {
        matrix[i][i] = 1;
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> unit_matrix(const size_t &m, const size_t &n) {
    std::vector<std::vector<T>> matrix(m, std::vector<T>(n));
    for (int i = 0; i < m; i++) {
        std::vector<T> row;
        row.resize(n);
        row[i] = static_cast<T>(1);
        matrix.push_back(row);
    }
    return matrix;
}

template <typename T>
std::vector<std::vector<T>> random_matrix(const size_t &m, const size_t &n, const T &low, const T &high) {
    std::vector<std::vector<T>> matrix(m, std::vector<T>(n));
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<T> distribution(low, high);
    for (size_t i = 0; i < m; i++) {
        std::vector<T> row;
        row.resize(n);
        for (auto &r : row) {
            r = distribution(generator);
        }
        matrix.push_back(row);
    }
    return matrix;
}

template <typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>> eigen(std::vector<std::vector<T>> x) {
    bool diagonal = true;
    std::map<int, int> valvec;
    std::vector<std::vector<T>> matrix;
    std::vector<std::vector<T>> eigenvectors = identity(x.size());
    do {
        T xij = x[0][1];
        T subi = 0, subj = 1;
        for (int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x[0].size(); j++) {
                if (i != j && std::abs(x[i][j]) > xij) {
                    xij = x[i][j];
                    subi = i;
                    subj = j;
                } else if (i != j && std::abs(x[i][j]) == xij) {
                    if (i < subi) {
                        xij = x[i][j];
                        subi = i;
                        subj = j;
                    }
                }
            }
        }
        T xii = x[subi][subi], xjj = x[subj][subj], xji = x[subj][subi], theta;
        theta = (xii == xjj) ? M_PI / 4 : 0.5 * atan(2 * xij / (xii - xjj));
        std::vector<std::vector<T>> P = identity(x.size());
        P[subi][subi] = std::cos(theta);
        P[subi][subj] = -std::sin(theta);
        P[subj][subi] = std::sin(theta);
        P[subj][subj] = std::cos(theta);

        matrix = matrixMultiply(matrixMultiply(inverse(P), x), P);
        bool nonzero = false;
        for (int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x.size(); j++) {
                if (i != j && std::round(matrix[i][j]) == 0) {
                    matrix[i][j] = 0;
                    nonzero = true;
                }
            }
        }
        diagonal = nonzero ? false : true;
        if (matrix == x) {
            diagonal = true;
            for (int i = 0; i < x.size(); i++) {
                for (int j = 0; j < x.size(); j++) {
                    if (i != j) matrix[i][j] = 0;
                }
            }
        }
        eigenvectors = matrixMultiply(eigenvectors, P);
        x = matrix;

    } while (!diagonal);

    std::vector<std::vector<T>> matcopy = matrix;
    for (int i = 0; i < matrix.size() - 1; i++) {
        for (int j = 0; j < matrix.size() - 1 - i; j++) {
            if (matrix[j][j] < matrix[j + 1][j + 1]) {
                T temp = matrix[j + 1][j + 1];
                matrix[j + 1][j + 1] = matrix[j][j];
                matrix[j][j] = temp;
            }
        }
    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[i][i] == matcopy[j][j]) {
                valvec[i] = j;
            }
        }
    }
    std::vector<std::vector<T>> temp = eigenvectors;
    for (int i = 0; i < eigenvectors.size(); i++) {
        for (int j = 0; j < eigenvectors[0].size(); j++) {
            eigenvectors[i][j] = temp[i][valvec[j]];
        }
    }

    return {eigenvectors, matrix};
}

template <typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>> qrDecomposition(std::vector<std::vector<T>> x) {
    std::vector<std::vector<T>> q = gramSchmidtProcess(x);
    std::vector<std::vector<T>> r = matrixMultiply(transpose(q), x);
    return {q, r};
}

template <typename T>
std::vector<std::vector<T>> gramSchmidtProcess(std::vector<std::vector<T>> x) {
    x = transpose(x);
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    matrix[0] = x[0];
    matrix[0] = scalarMultiply(matrix[0], 1 / norm(matrix[0]));
    for (int i = 1; i < matrix.size(); i++) {
        matrix[i] = x[i];
        for (int j = i - 1; j > -1; j--) {
            matrix[i] = subtract(matrix[i], vectorProjection(matrix[j], x[i]));
        }
        matrix[i] = scalarMultiply(matrix[i], 1 / norm(matrix[i]));
    }
    return transpose(matrix);
}

template <typename T>
std::vector<T> vectorProjection(std::vector<T> a, std::vector<T> b) {
    T scalar = dot(a, b) / dot(a, a);
    return scalarMultiply(a, scalar);
}

template <typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>, std::vector<std::vector<T>>> singularValueDecomposition(std::vector<std::vector<T>> x) {
    auto [leftvec, leftval] = eigen(matrixMultiply(x, transpose(x)));
    auto [rightvec, rightval] = eigen(matrixMultiply(transpose(x), x));
    std::vector<std::vector<T>> singular = elementWiseSqrt(leftval);
    std::vector<std::vector<T>> sigma = fillMatrix(x.size(), x[0].size(), 0);
    for (int i = 0; i < singular.size(); i++) {
        for (int j = 0; j < singular[0].size(); j++) {
            sigma[i][j] = singular[i][j];
        }
    }
    return {leftvec, sigma, rightvec};
}

template <typename T>
void printMatrix(std::vector<std::vector<T>> x) {
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            std::cout << x[i][j] << " ";
        }
        std::cout << std::endl;
    }
}