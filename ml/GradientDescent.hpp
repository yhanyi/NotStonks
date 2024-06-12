#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include <vector>

namespace MLCPP {
class GradientDescent {
   public:
    GradientDescent(double learning_rate);
    void update(std::vector<double>& weights, const std::vector<double>& gradients);

   private:
    double learning_rate_;
};
}  // namespace MLCPP

#endif  // GRADIENTDESCENT_HPP
