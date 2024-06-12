#ifndef PAIRSTRADING_HPP
#define PAIRSTRADING_HPP

#include <utility>
#include <vector>

class PairsTrading {
   public:
    static std::pair<double, double> calculate_spread(const std::vector<double>& prices1, const std::vector<double>& prices2);
    static std::pair<std::vector<double>, std::vector<double>> generate_signals(const std::vector<double>& spread, double entry_threshold, double exit_threshold);
};

#endif  // PAIRSTRADING_HPP
