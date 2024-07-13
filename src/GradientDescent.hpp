#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include <vector>

class GradientDescent {
   public:
    GradientDescent(double learning_rate) : learning_rate_(learning_rate) {}
    void update(std::vector<double>& weights, const std::vector<double>& gradients) {
        for (size_t i = 0; i < weights.size(); ++i) {
            weights[i] -= learning_rate_ * gradients[i];
        }
    }

   private:
    double learning_rate_;
};

#endif  // GRADIENTDESCENT_HPP
