#ifndef AUTOCORRELATION_HPP
#define AUTOCORRELATION_HPP

#include <cmath>
#include <numeric>
#include <vector>

class AutoCorrelation {
   public:
    static std::vector<double> calculate(const std::vector<double>& data, int lag) {
        std::vector<double> autocorrelations(lag + 1, 0.0);
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();

        for (int l = 0; l <= lag; ++l) {
            double numerator = 0.0;
            double denominator = 0.0;
            for (size_t i = l; i < data.size(); ++i) {
                numerator += (data[i] - mean) * (data[i - l] - mean);
                denominator += std::pow(data[i] - mean, 2);
            }
            autocorrelations[l] = numerator / denominator;
        }

        return autocorrelations;
    }
    static std::vector<double> partial(const std::vector<double>& data, int lag) {
        std::vector<double> pacf(lag + 1, 0.0);
        pacf[0] = 1.0;  // Partial auto-correlation at lag=0 is always 1

        for (int k = 1; k <= lag; ++k) {
            double num = 0.0, den = 0.0;
            for (int i = k; i < data.size(); ++i) {
                num += (data[i] - data[i - k]) * (data[i - k] - data[i - 2 * k]);
                den += (data[i - k] - data[i - 2 * k]) * (data[i - k] - data[i - 2 * k]);
            }
            pacf[k] = num / den;
        }

        return pacf;
    }
};

#endif  // AUTOCORRELATION_HPP
