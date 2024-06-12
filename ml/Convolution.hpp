#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include <vector>

namespace MLCPP {
class Convolution {
   public:
    std::vector<std::vector<double>> convolve(const std::vector<std::vector<double>>& input,
                                              const std::vector<std::vector<double>>& kernel);

   private:
    double applyKernel(const std::vector<std::vector<double>>& input,
                       const std::vector<std::vector<double>>& kernel, int x, int y);
};
}  // namespace MLCPP
#endif  // CONVOLUTION_HPP