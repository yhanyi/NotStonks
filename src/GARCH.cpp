#include "GARCH.hpp"

#include <cmath>
#include <vector>

// Simplified GARCH(1,1) implementation
std::vector<double> GARCH::fit(const std::vector<double>& data, int p, int q) {
    std::vector<double> variances(data.size(), 0.0);
    double alpha0 = 0.1;
    double alpha1 = 0.85;
    double beta1 = 0.1;

    variances[0] = data[0] * data[0];
    for (size_t t = 1; t < data.size(); ++t) {
        variances[t] = alpha0 + alpha1 * data[t - 1] * data[t - 1] + beta1 * variances[t - 1];
    }

    return variances;
}
