// HypothesisTesting.hpp

#ifndef HYPOTHESISTESTING_HPP
#define HYPOTHESISTESTING_HPP

#include <vector>

class HypothesisTesting {
   public:
    static std::pair<double, int> chiSquaredStatistic(std::vector<double> observed, std::vector<double> expected);
};

#endif  // HYPOTHESISTESTING_HPP