#ifndef RISKADJUSTEDPERFORMANCE_HPP
#define RISKADJUSTEDPERFORMANCE_HPP

#include <vector>

class RiskAdjustedPerformance {
   public:
    static double sharpe_ratio(const std::vector<double>& returns, double risk_free_rate);
    static double sortino_ratio(const std::vector<double>& returns, double risk_free_rate);
};

#endif  // RISKADJUSTEDPERFORMANCE_HPP
