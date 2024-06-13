#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include <tuple>
#include <vector>

class SparseMatrix {
   public:
    SparseMatrix(int rows, int cols);
    void addValue(int row, int col, double value);
    double getValue(int row, int col) const;
    SparseMatrix multiply(const SparseMatrix& other) const;

   private:
    int rows_, cols_;
    std::vector<std::tuple<int, int, double>> values_;
};

#endif  // SPARSEMATRIX_HPP
