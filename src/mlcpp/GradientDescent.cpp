#include "GradientDescent.hpp"

GradientDescent::GradientDescent(double learning_rate) : learning_rate_(learning_rate) {}

void GradientDescent::update(std::vector<double>& weights, const std::vector<double>& gradients) {
    for (size_t i = 0; i < weights.size(); ++i) {
        weights[i] -= learning_rate_ * gradients[i];
    }
};