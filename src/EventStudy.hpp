#ifndef EVENTSTUDY_HPP
#define EVENTSTUDY_HPP

#include <numeric>
#include <vector>

class EventStudy {
   public:
    static std::vector<double> calculate_abnormal_returns(const std::vector<double>& returns, const std::vector<double>& market_returns) {
        if (returns.size() != market_returns.size()) {
            throw std::invalid_argument("Returns series must have the same length");
        }

        std::vector<double> abnormal_returns(returns.size());
        for (size_t i = 0; i < returns.size(); ++i) {
            abnormal_returns[i] = returns[i] - market_returns[i];
        }

        return abnormal_returns;
    }

    static double cumulative_abnormal_return(const std::vector<double>& abnormal_returns) {
        return std::accumulate(abnormal_returns.begin(), abnormal_returns.end(), 0.0);
    }
};

#endif  // EVENTSTUDY_HPP
