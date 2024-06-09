#include "ARIMA.hpp"

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

// Helper function for differencing
std::vector<double> difference(const std::vector<double>& data, int d) {
    if (d <= 0) return data;
    std::vector<double> differenced_data;
    for (size_t i = d; i < data.size(); ++i) {
        differenced_data.push_back(data[i] - data[i - d]);
    }
    return differenced_data;
}

// Simplified ARIMA(p,d,q) fitting
std::vector<double> ARIMA::fit(const std::vector<double>& data, int p, int d, int q) {
    // Placeholder code for ARIMA model fitting
    std::vector<double> residuals = data;  // This is a simplification

    // Difference the data if d > 0
    for (int i = 0; i < d; ++i) {
        std::vector<double> differenced_data;
        for (size_t j = 1; j < residuals.size(); ++j) {
            differenced_data.push_back(residuals[j] - residuals[j - 1]);
        }
        residuals = differenced_data;
    }

    // Placeholder to simulate ARIMA(p,d,q) model result
    std::vector<double> result(residuals.size(), 0.0);
    for (size_t i = 0; i < residuals.size(); ++i) {
        if (i >= static_cast<size_t>(p)) {
            result[i] = std::accumulate(residuals.begin() + i - p, residuals.begin() + i, 0.0) / p;
        }
    }

    return result;
}

// Simplified ARIMA prediction
std::vector<double> ARIMA::predict(const std::vector<double>& fitted_values, int steps) {
    std::vector<double> predictions;
    for (int i = 0; i < steps; ++i) {
        double next_value = fitted_values.back();
        predictions.push_back(next_value);
    }
    return predictions;
}
