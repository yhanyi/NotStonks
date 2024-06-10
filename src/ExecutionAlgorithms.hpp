#ifndef EXECUTIONALGORITHMS_HPP
#define EXECUTIONALGORITHMS_HPP

#include <vector>

class ExecutionAlgorithms {
   public:
    static std::vector<double> vwap(const std::vector<double>& prices, const std::vector<int>& volumes);
    static std::vector<double> twap(const std::vector<double>& prices, int n);
};

#endif  // EXECUTIONALGORITHMS_HPP
