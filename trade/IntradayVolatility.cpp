#include "IntradayVolatility.hpp"

#include <cmath>
#include <numeric>

double IntradayVolatility::estimate(const std::vector<double>& prices, int interval) {
    std::vector<double> log_returns;
    for (size_t i = interval; i < prices.size(); i += interval) {
        double log_return = std::log(prices[i] / prices[i - interval]);
        log_returns.push_back(log_return);
    }

    double mean_return = std::accumulate(log_returns.begin(), log_returns.end(), 0.0) / log_returns.size();
    double variance = 0.0;
    for (double log_return : log_returns) {
        variance += std::pow(log_return - mean_return, 2);
    }
    variance /= log_returns.size();
    return std::sqrt(variance);
}
