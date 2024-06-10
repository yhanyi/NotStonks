#ifndef MEANREVERSION_HPP
#define MEANREVERSION_HPP

#include <vector>

class MeanReversion {
   public:
    static std::vector<int> generate_signals(const std::vector<double>& prices, double threshold);
};

#endif  // MEANREVERSION_HPP
