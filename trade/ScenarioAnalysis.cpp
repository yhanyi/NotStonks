#include "ScenarioAnalysis.hpp"

#include <algorithm>

double ScenarioAnalysis::calculate_portfolio_loss(const std::vector<double>& portfolio_values, double percentile) {
    std::vector<double> sorted_values = portfolio_values;
    std::sort(sorted_values.begin(), sorted_values.end());
    size_t index = static_cast<size_t>((1 - percentile) * portfolio_values.size());
    return sorted_values[index];
}
