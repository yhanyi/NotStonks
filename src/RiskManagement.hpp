#ifndef RISKMANAGEMENT_HPP
#define RISKMANAGEMENT_HPP

#include <vector>

class RiskManagement {
   public:
    static double stress_test(const std::vector<double>& portfolio_returns, double stress_factor);
};

#endif  // RISKMANAGEMENT_HPP
