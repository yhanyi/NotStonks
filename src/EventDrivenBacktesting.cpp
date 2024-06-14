#include "EventDrivenBacktesting.hpp"

double EventDrivenBacktesting::simulate(const std::vector<double>& prices, const std::vector<int>& signals, double initial_cash, double transaction_cost) {
    double cash = initial_cash;
    int shares = 0;

    for (size_t i = 0; i < prices.size(); ++i) {
        if (signals[i] == 1 && cash >= prices[i]) {  // Buy signal
            shares += 1;
            cash -= prices[i] + transaction_cost;
        } else if (signals[i] == -1 && shares > 0) {  // Sell signal
            shares -= 1;
            cash += prices[i] - transaction_cost;
        }
    }

    return cash + shares * prices.back();
}
