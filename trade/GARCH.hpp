#ifndef GARCH_HPP
#define GARCH_HPP

#include <vector>

class GARCH {
   public:
    static std::vector<double> fit(const std::vector<double>& data, int p, int q);
};

#endif  // GARCH_HPP
