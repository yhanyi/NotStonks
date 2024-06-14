#ifndef RISKMETRICS_HPP
#define RISKMETRICS_HPP

#include <vector>

class RiskMetrics {
   public:
    static double value_at_risk(const std::vector<double>& returns, double confidence_level);
    static double conditional_value_at_risk(const std::vector<double>& returns, double confidence_level);
    static double sharpe_ratio(const std::vector<double>& returns, double risk_free_rate);
};

#endif  // RISKMETRICS_HPP
