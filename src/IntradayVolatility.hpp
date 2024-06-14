#ifndef INTRADAYVOLATILITY_HPP
#define INTRADAYVOLATILITY_HPP

#include <vector>

class IntradayVolatility {
   public:
    static double estimate(const std::vector<double>& prices, int interval);
};

#endif  // INTRADAYVOLATILITY_HPP
