#ifndef LIQUIDITYMETRICS_HPP
#define LIQUIDITYMETRICS_HPP

#include <utility>
#include <vector>

class LiquidityMetrics {
   public:
    static double calculate_amihud(const std::vector<double>& returns, const std::vector<int>& volumes);
    static std::pair<double, double> calculate_spread(const std::vector<double>& bids, const std::vector<double>& asks);
};

#endif  // LIQUIDITYMETRICS_HPP
