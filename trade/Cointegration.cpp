#include "Cointegration.hpp"

#include <cmath>
#include <numeric>

// Simplified cointegration test (e.g., Engle-Granger test)
double Cointegration::test(const std::vector<double>& x, const std::vector<double>& y) {
    double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

    double covariance = 0.0;
    double variance_x = 0.0;
    double variance_y = 0.0;

    for (size_t i = 0; i < x.size(); ++i) {
        covariance += (x[i] - mean_x) * (y[i] - mean_y);
        variance_x += (x[i] - mean_x) * (x[i] - mean_x);
        variance_y += (y[i] - mean_y) * (y[i] - mean_y);
    }

    double correlation = covariance / std::sqrt(variance_x * variance_y);
    return correlation;
}
