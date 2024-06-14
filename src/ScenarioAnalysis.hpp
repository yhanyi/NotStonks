#ifndef SCENARIOANALYSIS_HPP
#define SCENARIOANALYSIS_HPP

#include <vector>

class ScenarioAnalysis {
   public:
    static double calculate_portfolio_loss(const std::vector<double>& portfolio_values, double percentile);
};

#endif  // SCENARIOANALYSIS_HPP
