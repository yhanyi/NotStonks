#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include <vector>

class Convolution {
   public:
    std::vector<std::vector<double>> convolve(const std::vector<std::vector<double>>& input,
                                              const std::vector<std::vector<double>>& kernel);

   private:
    double applyKernel(const std::vector<std::vector<double>>& input,
                       const std::vector<std::vector<double>>& kernel, int x, int y);
};
#endif  // CONVOLUTION_HPP