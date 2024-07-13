#ifndef PAIRSTRADING_HPP
#define PAIRSTRADING_HPP

#include <cmath>
#include <numeric>
#include <utility>
#include <vector>

class PairsTrading {
   public:
    static std::pair<double, double> calculate_spread(const std::vector<double>& prices1, const std::vector<double>& prices2) {
        if (prices1.size() != prices2.size()) {
            throw std::invalid_argument("Price series must have the same length");
        }

        std::vector<double> spread(prices1.size());
        for (size_t i = 0; i < prices1.size(); ++i) {
            spread[i] = prices1[i] - prices2[i];
        }

        double mean_spread = std::accumulate(spread.begin(), spread.end(), 0.0) / spread.size();
        double sum_sq_diff = 0.0;
        for (double s : spread) {
            sum_sq_diff += std::pow(s - mean_spread, 2);
        }
        double std_dev_spread = std::sqrt(sum_sq_diff / spread.size());

        return {mean_spread, std_dev_spread};
    }

    static std::pair<std::vector<double>, std::vector<double>> generate_signals(const std::vector<double>& spread, double entry_threshold, double exit_threshold) {
        std::vector<double> long_signals(spread.size(), 0);
        std::vector<double> short_signals(spread.size(), 0);

        for (size_t i = 1; i < spread.size(); ++i) {
            if (spread[i] < -entry_threshold) {
                long_signals[i] = 1;
            } else if (spread[i] > exit_threshold) {
                long_signals[i] = 0;
            }

            if (spread[i] > entry_threshold) {
                short_signals[i] = -1;
            } else if (spread[i] < -exit_threshold) {
                short_signals[i] = 0;
            }
        }
        return {long_signals, short_signals};
    }
};

#endif  // PAIRSTRADING_HPP
