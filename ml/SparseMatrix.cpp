#include "SparseMatrix.hpp"

#include <unordered_map>

namespace MLCPP {
SparseMatrix::SparseMatrix(int rows, int cols) : rows_(rows), cols_(cols) {}

void SparseMatrix::addValue(int row, int col, double value) {
    values_.emplace_back(row, col, value);
}

double SparseMatrix::getValue(int row, int col) const {
    for (const auto& [r, c, v] : values_) {
        if (r == row && c == col) {
            return v;
        }
    }
    return 0.0;
}

SparseMatrix SparseMatrix::multiply(const SparseMatrix& other) const {
    SparseMatrix result(rows_, other.cols_);
    std::unordered_map<int, std::unordered_map<int, double>> other_map;

    for (const auto& [r, c, v] : other.values_) {
        other_map[r][c] = v;
    }

    for (const auto& [r, c, v] : values_) {
        for (int k = 0; k < other.cols_; ++k) {
            if (other_map.count(c) && other_map[c].count(k)) {
                result.addValue(r, k, v * other_map[c][k]);
            }
        }
    }

    return result;
}
}  // namespace MLCPP