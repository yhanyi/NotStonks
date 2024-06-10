#include "LiquidityMetrics.hpp"

#include <cmath>
#include <numeric>

double LiquidityMetrics::calculate_amihud(const std::vector<double>& returns, const std::vector<int>& volumes) {
    double amihud = 0.0;
    for (size_t i = 0; i < returns.size(); ++i) {
        amihud += std::abs(returns[i]) / volumes[i];
    }
    return amihud / returns.size();
}

std::pair<double, double> LiquidityMetrics::calculate_spread(const std::vector<double>& bids, const std::vector<double>& asks) {
    double bid_ask_spread = 0.0;
    double bid_ask_midpoint = 0.0;
    for (size_t i = 0; i < bids.size(); ++i) {
        bid_ask_spread += asks[i] - bids[i];
        bid_ask_midpoint += (asks[i] + bids[i]) / 2.0;
    }
    return std::make_pair(bid_ask_spread / bids.size(), bid_ask_midpoint / bids.size());
}
