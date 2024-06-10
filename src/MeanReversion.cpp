#include "MeanReversion.hpp"

#include <cmath>
#include <numeric>

std::vector<int> MeanReversion::generate_signals(const std::vector<double>& prices, double threshold) {
    std::vector<int> signals(prices.size(), 0);

    double mean_price = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
    double variance = 0.0;
    for (const double& price : prices) {
        variance += std::pow(price - mean_price, 2);
    }
    variance /= prices.size();
    double stddev = std::sqrt(variance);

    for (size_t i = 0; i < prices.size(); ++i) {
        if (prices[i] > mean_price + threshold * stddev) {
            signals[i] = -1;  // Sell signal
        } else if (prices[i] < mean_price - threshold * stddev) {
            signals[i] = 1;  // Buy signal
        }
    }

    return signals;
}
