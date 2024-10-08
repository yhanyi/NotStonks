#ifndef POOLING_HPP
#define POOLING_HPP

#include <vector>

class Pooling {
   public:
    enum class PoolingType { MAX,
                             AVERAGE };

    std::vector<std::vector<double>> pool(const std::vector<std::vector<double>>& input,
                                          int poolSize, PoolingType type) {
        int rows = input.size();
        int cols = input[0].size();
        std::vector<std::vector<double>> output(rows / poolSize, std::vector<double>(cols / poolSize, 0));

        for (int i = 0; i < rows; i += poolSize) {
            for (int j = 0; j < cols; j += poolSize) {
                if (type == PoolingType::MAX) {
                    output[i / poolSize][j / poolSize] = applyMaxPooling(input, i, j, poolSize);
                } else if (type == PoolingType::AVERAGE) {
                    output[i / poolSize][j / poolSize] = applyAveragePooling(input, i, j, poolSize);
                }
            }
        }

        return output;
    }

   private:
    double applyMaxPooling(const std::vector<std::vector<double>>& input, int x, int y, int poolSize) {
        double maxVal = -std::numeric_limits<double>::infinity();
        for (int i = 0; i < poolSize; ++i) {
            for (int j = 0; j < poolSize; ++j) {
                maxVal = std::max(maxVal, input[x + i][y + j]);
            }
        }
        return maxVal;
    }

    double applyAveragePooling(const std::vector<std::vector<double>>& input, int x, int y, int poolSize) {
        double sum = 0.0;
        for (int i = 0; i < poolSize; ++i) {
            for (int j = 0; j < poolSize; ++j) {
                sum += input[x + i][y + j];
            }
        }
        return sum / (poolSize * poolSize);
    }
};
#endif  // POOLING_HPP