// HypothesisTesting.hpp

#ifndef HYPOTHESISTESTING_HPP
#define HYPOTHESISTESTING_HPP

#include <vector>

namespace MLCPP {
class HypothesisTesting {
   public:
    std::pair<double, int> chiSquaredStatistic(std::vector<double> observed, std::vector<double> expected);
};
}  // namespace MLCPP

#endif  // HYPOTHESISTESTING_HPP