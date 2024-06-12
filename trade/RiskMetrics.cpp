#include "RiskMetrics.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

#include "Analysis.hpp"

double RiskMetrics::value_at_risk(const std::vector<double>& returns, double confidence_level) {
    std::vector<double> sorted_returns = returns;
    std::sort(sorted_returns.begin(), sorted_returns.end());
    size_t index = static_cast<size_t>((1 - confidence_level) * sorted_returns.size());
    return sorted_returns[index];
}

double RiskMetrics::conditional_value_at_risk(const std::vector<double>& returns, double confidence_level) {
    double var = value_at_risk(returns, confidence_level);
    double cvar = 0.0;
    size_t count = 0;

    for (double return_value : returns) {
        if (return_value < var) {
            cvar += return_value;
            ++count;
        }
    }

    return cvar / count;
}

double RiskMetrics::sharpe_ratio(const std::vector<double>& returns, double risk_free_rate) {
    double mean_return = Analysis::mean(returns);
    double std_dev = Analysis::standard_deviation(returns);
    return (mean_return - risk_free_rate) / std_dev;
}
