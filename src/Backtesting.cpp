#include "Backtesting.hpp"

#include "Analysis.hpp"

double Backtesting::run_backtest(const std::vector<double>& prices, const std::string& strategy) {
    double initial_balance = 10000.0;  // starting with $10,000
    double balance = initial_balance;
    double shares = 0.0;

    if (strategy == "SMA") {
        int window_size = 20;
        std::vector<double> sma = Analysis::simple_moving_average(prices, window_size);

        for (size_t i = window_size; i < prices.size(); ++i) {
            if (prices[i] > sma[i - window_size]) {
                shares = balance / prices[i];
                balance = 0.0;
            } else if (prices[i] < sma[i - window_size]) {
                balance = shares * prices[i];
                shares = 0.0;
            }
        }

        if (shares > 0) {
            balance = shares * prices.back();
        }
    }

    return balance - initial_balance;
}
