#include "AdamOptimizer.hpp"

#include <cmath>

AdamOptimizer::AdamOptimizer(double learning_rate, double beta1, double beta2, double epsilon)
    : learning_rate_(learning_rate), beta1_(beta1), beta2_(beta2), epsilon_(epsilon), t_(0) {}

void AdamOptimizer::update(std::vector<double>& weights, const std::vector<double>& gradients) {
    t_++;
    for (size_t i = 0; i < weights.size(); ++i) {
        m_[i] = beta1_ * m_[i] + (1 - beta1_) * gradients[i];
        v_[i] = beta2_ * v_[i] + (1 - beta2_) * gradients[i] * gradients[i];
        double m_hat = m_[i] / (1 - std::pow(beta1_, t_));
        double v_hat = v_[i] / (1 - std::pow(beta2_, t_));
        weights[i] -= learning_rate_ * m_hat / (std::sqrt(v_hat) + epsilon_);
    }
};