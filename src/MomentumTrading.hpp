#ifndef MOMENTUMTRADING_HPP
#define MOMENTUMTRADING_HPP

#include <vector>

#include "TradingAlgorithm.hpp"

class MomentumTrading : public TradingAlgorithm {
   public:
    MomentumTrading(BrokerAPI& api, std::mutex& logMutex, double cash, int shares) : TradingAlgorithm(api, logMutex, cash, shares) {}
    void run() override;
    void trade() override;

   private:
    std::vector<double> calculate_rsi(const std::vector<double>& prices, int period);
    std::vector<int> generate_signals(const std::vector<double>& rsi, double rsi_buy_threshold, double rsi_sell_threshold);
    double backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash);
    void optimize_parameters(const std::vector<double>& prices);
};

#endif  // MOMENTUMTRADING_HPP
