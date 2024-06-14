#include "HypothesisTesting.hpp"

#include <vector>

std::pair<double, int> chiSquaredStatistic(std::vector<double> observed, std::vector<double> expected) {
    double df = observed.size() - 1;
    double total = 0;
    for (int i = 0; i < observed.size(); i++) {
        total += (observed[i] - expected[i]) * (observed[i] - expected[i]) / expected[i];
    }
    return std::make_pair(total, df);
}