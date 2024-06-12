#ifndef PORTFOLIOOPTIMIZATION_HPP
#define PORTFOLIOOPTIMIZATION_HPP

#include <vector>

class PortfolioOptimization {
   public:
    static std::vector<double> optimize(const std::vector<std::vector<double>>& returns, double risk_free_rate);
};

#endif  // PORTFOLIOOPTIMIZATION_HPP
