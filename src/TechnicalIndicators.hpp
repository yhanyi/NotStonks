#ifndef TECHNICALINDICATORS_HPP
#define TECHNICALINDICATORS_HPP

#include <vector>

class TechnicalIndicators {
   public:
    static std::vector<double> relative_strength_index(const std::vector<double>& data, int window_size);
    static std::vector<double> macd(const std::vector<double>& data, int short_window, int long_window, int signal_window);
};

#endif  // TECHNICALINDICATORS_HPP
