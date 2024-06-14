#include "Transforms.hpp"

#include <string>
#include <vector>

#include "LinearAlgebra.hpp"

template <typename T>
std::vector<std::vector<T>> Transforms::discreteCosineTransform(std::vector<std::vector<T>> x) {
    x = LinearAlgebra::scalarAdd(x, -128);
    std::vector<std::vector<T>> matrix(x.size(), std::vector<T>(x[0].size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            T total = 0;
            T alpha_i = (i == 0) ? 1 / std::sqrt(x.size()) : std::sqrt(2.0 / x.size());
            T alpha_j = (j == 0) ? 1 / std::sqrt(x.size()) : std::sqrt(2.0 / x.size());
            for (int k = 0; k < matrix.size(); k++) {
                for (int l = 0; l < matrix[0].size(); l++) {
                    total += x[k][l] * std::cos((M_PI * i * (2 + k + 1)) / (2 * x.size())) * std::cos((M_PI * j * (2 * l + 1)) / (2 * x.size()));
                }
            }
            matrix[i][j] = total * alpha_i * alpha_j;
        }
    }
    return matrix;
}