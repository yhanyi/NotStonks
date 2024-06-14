#ifndef EVENTDRIVENBACKTESTING_HPP
#define EVENTDRIVENBACKTESTING_HPP

#include <vector>

class EventDrivenBacktesting {
   public:
    static double simulate(const std::vector<double>& prices, const std::vector<int>& signals, double initial_cash, double transaction_cost);
};

#endif  // EVENTDRIVENBACKTESTING_HPP
