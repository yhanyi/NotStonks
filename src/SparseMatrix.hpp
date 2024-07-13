#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include <tuple>
#include <unordered_map>
#include <vector>

class SparseMatrix {
   public:
    SparseMatrix(int rows, int cols) : rows_(rows), cols_(cols) {}
    void addValue(int row, int col, double value) { values_.emplace_back(row, col, value); }
    double getValue(int row, int col) const {
        for (const auto& [r, c, v] : values_) {
            if (r == row && c == col) {
                return v;
            }
        }
        return 0.0;
    }
    SparseMatrix multiply(const SparseMatrix& other) const {
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

   private:
    int rows_, cols_;
    std::vector<std::tuple<int, int, double>> values_;
};

#endif  // SPARSEMATRIX_HPP
