#ifndef MOMENTUMTRADING_HPP
#define MOMENTUMTRADING_HPP

#include <vector>

class MomentumTrading {
   public:
    static std::vector<double> calculate_rsi(const std::vector<double>& prices, int period);
    static std::vector<int> generate_signals(const std::vector<double>& rsi, double rsi_buy_threshold, double rsi_sell_threshold);
    static double backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash);
    static void optimize_parameters(const std::vector<double>& prices);
};

#endif  // MOMENTUMTRADING_HPP
