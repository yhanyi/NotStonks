#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include <tuple>
#include <vector>

namespace MLCPP {
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
}  // namespace MLCPP

#endif  // SPARSEMATRIX_HPP
