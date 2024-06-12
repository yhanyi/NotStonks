#ifndef ARIMA_HPP
#define ARIMA_HPP

#include <vector>

class ARIMA {
   public:
    static std::vector<double> fit(const std::vector<double>& data, int p, int d, int q);
    static std::vector<double> predict(const std::vector<double>& fitted_values, int steps);
};

#endif  // ARIMA_HPP
