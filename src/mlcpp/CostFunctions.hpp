// CostFunctions.hpp

#ifndef COSTFUNCTIONS_HPP
#define COSTFUNCTIONS_HPP

#include <vector>

class CostFunctions {
   public:
    // Classification Cost Functions
    double logLoss(std::vector<double> y, std::vector<double> y_hat);

    double crossEntropy(std::vector<double> y, std::vector<double> y_hat);

    double huberLoss(std::vector<double> y, std::vector<double> y_hat, double delta);

    double hingeLoss(std::vector<double> y, std::vector<double> y_hat);

    double wassersteinLoss(std::vector<double> y, std::vector<double> y_hat);

    // Regression Cost Functions
    double mse(std::vector<double> y, std::vector<double> y_hat);

    double rmse(std::vector<double> y, std::vector<double> y_hat);

    double mae(std::vector<double> y, std::vector<double> y_hat);

    double mbe(std::vector<double> y, std::vector<double> y_hat);
};

#endif  // COSTFUNCTIONS_HPP