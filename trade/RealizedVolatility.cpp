#include "RealizedVolatility.hpp"

#include <cmath>
#include <numeric>

double RealizedVolatility::calculate(const std::vector<double>& intraday_prices) {
    std::vector<double> log_returns;
    for (size_t i = 1; i < intraday_prices.size(); ++i) {
        log_returns.push_back(std::log(intraday_prices[i] / intraday_prices[i - 1]));
    }

    double mean_return = std::accumulate(log_returns.begin(), log_returns.end(), 0.0) / log_returns.size();
    double variance = 0.0;
    for (const double& ret : log_returns) {
        variance += std::pow(ret - mean_return, 2);
    }
    variance /= log_returns.size();

    return std::sqrt(variance) * std::sqrt(252);  // Annualize the volatility assuming 252 trading days
}
