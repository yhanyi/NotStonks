#ifndef ORDERFLOWANALYSIS_HPP
#define ORDERFLOWANALYSIS_HPP

#include <utility>
#include <vector>

class OrderFlowAnalysis {
   public:
    static double calculate_order_imbalance(const std::vector<int>& buy_volumes, const std::vector<int>& sell_volumes);
    static std::vector<std::pair<double, double>> calculate_cumulative_order_flow(const std::vector<double>& prices, const std::vector<int>& volumes);
};

#endif  // ORDERFLOWANALYSIS_HPP
