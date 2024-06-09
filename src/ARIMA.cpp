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
    // Step 1: Difference the data to make it stationary
    std::vector<double> differenced_data = difference(data, d);

    // Placeholder for actual ARIMA model fitting
    // Here we just return the differenced data as a placeholder
    return differenced_data;
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
