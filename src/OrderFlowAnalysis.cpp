#include "OrderFlowAnalysis.hpp"

#include <numeric>

double OrderFlowAnalysis::calculate_order_imbalance(const std::vector<int>& buy_volumes, const std::vector<int>& sell_volumes) {
    int total_buy = std::accumulate(buy_volumes.begin(), buy_volumes.end(), 0);
    int total_sell = std::accumulate(sell_volumes.begin(), sell_volumes.end(), 0);
    return static_cast<double>(total_buy - total_sell) / (total_buy + total_sell);
}

std::vector<std::pair<double, double>> OrderFlowAnalysis::calculate_cumulative_order_flow(const std::vector<double>& prices, const std::vector<int>& volumes) {
    std::vector<std::pair<double, double>> order_flow;
    double cumulative_volume = 0.0;
    double cumulative_value = 0.0;

    for (size_t i = 0; i < prices.size(); ++i) {
        cumulative_volume += volumes[i];
        cumulative_value += prices[i] * volumes[i];
        order_flow.push_back(std::make_pair(cumulative_volume, cumulative_value));
    }

    return order_flow;
}
