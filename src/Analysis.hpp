#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <vector>

class Analysis {
   public:
    static double mean(const std::vector<double>& data);
    static double median(std::vector<double> data);
    static double variance(const std::vector<double>& data);
    static double standard_deviation(const std::vector<double>& data);

    static std::vector<double> simple_moving_average(const std::vector<double>& data, int window_size);
    static std::vector<double> exponential_moving_average(const std::vector<double>& data, int window_size);
};

#endif  // ANALYSIS_HPP