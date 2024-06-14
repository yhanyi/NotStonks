#ifndef AUTOCORRELATION_HPP
#define AUTOCORRELATION_HPP

#include <vector>

class AutoCorrelation {
   public:
    static std::vector<double> calculate(const std::vector<double>& data, int lag);
    static std::vector<double> partial(const std::vector<double>& data, int lag);
};

#endif  // AUTOCORRELATION_HPP
