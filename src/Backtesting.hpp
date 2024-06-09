#ifndef BACKTESTING_HPP
#define BACKTESTING_HPP

#include <string>
#include <vector>

class Backtesting {
   public:
    static double run_backtest(const std::vector<double>& prices, const std::string& strategy);
};

#endif  // BACKTESTING_HPP
