#include "Convolution.hpp"

namespace MLCPP {
std::vector<std::vector<double>> Convolution::convolve(const std::vector<std::vector<double>>& input,
                                                       const std::vector<std::vector<double>>& kernel) {
    int rows = input.size();
    int cols = input[0].size();
    int kSize = kernel.size();
    int kHalf = kSize / 2;
    std::vector<std::vector<double>> output(rows, std::vector<double>(cols, 0));

    for (int i = kHalf; i < rows - kHalf; ++i) {
        for (int j = kHalf; j < cols - kHalf; ++j) {
            output[i][j] = applyKernel(input, kernel, i, j);
        }
    }

    return output;
}

double Convolution::applyKernel(const std::vector<std::vector<double>>& input,
                                const std::vector<std::vector<double>>& kernel, int x, int y) {
    int kSize = kernel.size();
    int kHalf = kSize / 2;
    double sum = 0.0;

    for (int i = -kHalf; i <= kHalf; ++i) {
        for (int j = -kHalf; j <= kHalf; ++j) {
            sum += input[x + i][y + j] * kernel[i + kHalf][j + kHalf];
        }
    }

    return sum;
}
}  // namespace MLCPP