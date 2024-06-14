#ifndef REALIZEDVOLATILITY_HPP
#define REALIZEDVOLATILITY_HPP

#include <vector>

class RealizedVolatility {
   public:
    static double calculate(const std::vector<double>& intraday_prices);
};

#endif  // REALIZEDVOLATILITY_HPP
