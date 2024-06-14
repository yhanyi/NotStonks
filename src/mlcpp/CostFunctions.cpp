#include "CostFunctions.hpp"

#include <vector>

// Classification Cost Functions
double logLoss(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += y[i] * std::log(y_hat[i]) + (1 - y[i]) * std::log(1 - y_hat[i]);
    }
    return -total / y.size();
}

double crossEntropy(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += y[i] * std::log(y_hat[i]);
    }
    return -total;
}

double huberLoss(std::vector<double> y, std::vector<double> y_hat, double delta) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += (std::abs(y[i] - y_hat[i] <= delta)) ? 0.5 * (y[i] - y_hat[i]) * (y[i] - y_hat[i]) : delta * (std::abs(y[i] - y_hat[i]) - 0.5 * delta);
    }
    return total / y.size();
}

double hingeLoss(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += fmax(0, 1 - y[i] * y_hat[i]);
    }
    return total / y.size();
}

double wassersteinLoss(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += y[i] * y_hat[i];
    }
    return -total / y.size();
}

// Regression Cost Functions
double mse(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += (y[i] - y_hat[i]) * (y[i] - y_hat[i]);
    }
    return total / y.size();
}

double rmse(std::vector<double> y, std::vector<double> y_hat) {
    return std::sqrt(mse(y, y_hat));
}

double mae(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += std::abs(y[i] - y_hat[i]);
    }
    return total / y.size();
}

double mbe(std::vector<double> y, std::vector<double> y_hat) {
    double total = 0;
    for (int i = 0; i < y.size(); i++) {
        total += y[i] - y_hat[i];
    }
    return total / y.size();
}