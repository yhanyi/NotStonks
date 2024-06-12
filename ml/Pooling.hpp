#ifndef POOLING_HPP
#define POOLING_HPP

#include <vector>

namespace MLCPP {
class Pooling {
   public:
    enum class PoolingType { MAX,
                             AVERAGE };

    std::vector<std::vector<double>> pool(const std::vector<std::vector<double>>& input,
                                          int poolSize, PoolingType type);

   private:
    double applyMaxPooling(const std::vector<std::vector<double>>& input, int x, int y, int poolSize);
    double applyAveragePooling(const std::vector<std::vector<double>>& input, int x, int y, int poolSize);
};
}  // namespace MLCPP
#endif  // POOLING_HPP