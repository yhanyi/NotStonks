#include "RiskAdjustedPerformance.hpp"

#include <cmath>
#include <numeric>

double RiskAdjustedPerformance::sharpe_ratio(const std::vector<double>& returns, double risk_free_rate) {
    double mean_return = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double excess_return = mean_return - risk_free_rate;

    double variance = 0.0;
    for (const double& ret : returns) {
        variance += std::pow(ret - mean_return, 2);
    }
    variance /= returns.size();

    double stddev = std::sqrt(variance);
    return excess_return / stddev;
}

double RiskAdjustedPerformance::sortino_ratio(const std::vector<double>& returns, double risk_free_rate) {
    double mean_return = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    double excess_return = mean_return - risk_free_rate;

    double downside_variance = 0.0;
    for (const double& ret : returns) {
        if (ret < risk_free_rate) {
            downside_variance += std::pow(ret - risk_free_rate, 2);
        }
    }
    downside_variance /= returns.size();

    double downside_stddev = std::sqrt(downside_variance);
    return excess_return / downside_stddev;
}
