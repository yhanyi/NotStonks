#ifndef MEANREVERSION_HPP
#define MEANREVERSION_HPP

#include <vector>

class MeanReversion {
   public:
    static std::vector<double> calculate_moving_average(const std::vector<double>& data, int window_size);
    static std::vector<double> calculate_standard_deviation(const std::vector<double>& data, int window_size);
    static std::vector<double> calculate_z_score(const std::vector<double>& data, int window_size);
    static std::vector<int> generate_signals(const std::vector<double>& z_score, double entry_threshold, double exit_threshold, int holding_period);
    static double backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash);
    static void optimize_parameters(const std::vector<double>& prices);
};

#endif  // MEANREVERSION_HPP
