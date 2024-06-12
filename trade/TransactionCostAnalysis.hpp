#ifndef TRANSACTIONCOSTANALYSIS_HPP
#define TRANSACTIONCOSTANALYSIS_HPP

#include <vector>

class TransactionCostAnalysis {
   public:
    static double calculate_total_cost(const std::vector<double>& prices, const std::vector<int>& volumes, double commission_rate);
};

#endif  // TRANSACTIONCOSTANALYSIS_HPP
