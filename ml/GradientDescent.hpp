#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include <vector>

class GradientDescent {
   public:
    GradientDescent(double learning_rate);
    void update(std::vector<double>& weights, const std::vector<double>& gradients);

   private:
    double learning_rate_;
};

#endif  // GRADIENTDESCENT_HPP
