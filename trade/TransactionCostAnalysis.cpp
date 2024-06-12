#include "TransactionCostAnalysis.hpp"

double TransactionCostAnalysis::calculate_total_cost(const std::vector<double>& prices, const std::vector<int>& volumes, double commission_rate) {
    double total_cost = 0.0;
    for (size_t i = 0; i < prices.size(); ++i) {
        total_cost += prices[i] * volumes[i] * commission_rate;
    }
    return total_cost;
}
