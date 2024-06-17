#ifndef MEANREVERSION_HPP
#define MEANREVERSION_HPP

#include <vector>

#include "TradingAlgorithm.hpp"

class MeanReversion : public TradingAlgorithm {
   public:
    MeanReversion(BrokerAPI& api, std::mutex& logMutex, double cash, int shares) : TradingAlgorithm(api, logMutex, cash, shares) {}
    void run() override;
    void trade() override;

   private:
    std::vector<double> calculate_moving_average(const std::vector<double>& data, int window_size);
    std::vector<double> calculate_standard_deviation(const std::vector<double>& data, int window_size);
    std::vector<double> calculate_z_score(const std::vector<double>& data, int window_size);
    std::vector<int> generate_signals(const std::vector<double>& z_scores, double entry_threshold, double exit_threshold, int holding_period);
    double backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash);
    void optimize_parameters(const std::vector<double>& prices);
};

#endif  // MEANREVERSION_HPP
