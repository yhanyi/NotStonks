#ifndef COINTEGRATION_HPP
#define COINTEGRATION_HPP

#include <vector>

class Cointegration {
   public:
    static double test(const std::vector<double>& x, const std::vector<double>& y);
};

#endif  // COINTEGRATION_HPP
