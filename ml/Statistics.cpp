#include "Statistics.hpp"

#include <vector>

namespace MLCPP {
class Statistics {
   public:
    double mean(std::vector<double> x) {
        double total = 0;
        for (int i = 0; i < x.size(); i++) {
            total += x[i];
        }
        return total / x.size();
    }

    double median(std::vector<double> x) {
        sort(x.begin(), x.end());
        return (x.size() % 2) ? x[x.size() / 2 + 1] : mean({x[x.size() / 2 - 1], x[x.size() / 2]});
    }

    double mode(std::vector<double> x) { ; }

    double standardDeviation(std::vector<double> x) {
        return std::sqrt(variance(x));
    }

    double variance(std::vector<double> x) {
        double total = 0;
        double m = mean(x);
        for (int i = 0; i < x.size(); i++) {
            total += (x[i] - m) * (x[i] - m);
        }
        return total / (x.size() - 1);
    }

    double covariance(std::vector<double> x, std::vector<double> y) {
        double total = 0;
        double m = mean(x), n = mean(y);
        for (int i = 0; i < x.size(); i++) {
            total += (x[i] - m) * (y[i] - n);
        }
        return total / (x.size() - 1);
    }

    double correlation(std::vector<double> x, std::vector<double> y) {
        return covariance(x, y) / (standardDeviation(x) * standardDeviation(y));
    }

    double chebyshev(double k) {
        return 1 - 1 / (k * k);
    }

    double weightedMean(std::vector<double> x, std::vector<double> y) { ; }

    double geometricMean(std::vector<double> x) { ; }

    double harmonicMean(std::vector<double> x) { ; }

    double rms(std::vector<double> x) { ; }

    double powerMean(std::vector<double> x, double k) { ; }

    double lehmerMean(std::vector<double> x, double k) { ; }

    double weightedLehmerMean(std::vector<double> x, std::vector<double> y, double k) { ; }

    double contraHarmonicMean(std::vector<double> x) { ; }

    double logMean(double x, double y) { ; }

    double stolarskyMean(double x, double y, double z) { ; }
};
}  // namespace MLCPP