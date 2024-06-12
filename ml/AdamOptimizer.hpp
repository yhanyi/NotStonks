#ifndef ADAM_OPTIMIZER_HPP
#define ADAM_OPTIMIZER_HPP

#include <vector>

namespace MLCPP {
class AdamOptimizer {
   public:
    AdamOptimizer(double learning_rate, double beta1, double beta2, double epsilon);
    void update(std::vector<double>& weights, const std::vector<double>& gradients);

   private:
    double learning_rate_;
    double beta1_, beta2_, epsilon_;
    std::vector<double> m_, v_;
    int t_;
};
}  // namespace MLCPP

#endif  // ADAM_OPTIMIZER_HPP
