// Statistics_hpp

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

namespace MLCPP {
class Statistics {
   public:
    static double mean(std::vector<double> x);

    static double median(std::vector<double> x);

    static double mode(std::vector<double> x);

    static double standardDeviation(std::vector<double> x);

    static double variance(std::vector<double> x);

    static double covariance(std::vector<double> x, std::vector<double> y);

    static double correlation(std::vector<double> x, std::vector<double> y);

    static double chebyshev(double k);

    static double weightedMean(std::vector<double> x, std::vector<double> y);

    static double geometricMean(std::vector<double> x);

    static double harmonicMean(std::vector<double> x);

    static double rms(std::vector<double> x);

    static double powerMean(std::vector<double> x, double k);

    static double lehmerMean(std::vector<double> x, double k);
    static double weightedLehmerMean(std::vector<double> x, std::vector<double> y, double k);

    static double contraHarmonicMean(std::vector<double> x);

    static double logMean(double x, double y);

    static double stolarskyMean(double x, double y, double z);
};
}  // namespace MLCPP

#endif  // STATISTICS_HPP