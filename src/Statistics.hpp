// Statistics_hpp

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

class Statistics {
   public:
    static double mean(std::vector<double> x) {
        double total = 0;
        for (int i = 0; i < x.size(); i++) {
            total += x[i];
        }
        return total / x.size();
    }

    static double median(std::vector<double> x) {
        sort(x.begin(), x.end());
        return (x.size() % 2) ? x[x.size() / 2 + 1] : mean({x[x.size() / 2 - 1], x[x.size() / 2]});
    }

    static double mode(std::vector<double> x) { return 0.0; }

    static double standardDeviation(std::vector<double> x) {
        return std::sqrt(variance(x));
    }

    static double variance(std::vector<double> x) {
        double total = 0;
        double m = mean(x);
        for (int i = 0; i < x.size(); i++) {
            total += (x[i] - m) * (x[i] - m);
        }
        return total / (x.size() - 1);
    }

    static double covariance(std::vector<double> x, std::vector<double> y) {
        double total = 0;
        double m = mean(x), n = mean(y);
        for (int i = 0; i < x.size(); i++) {
            total += (x[i] - m) * (y[i] - n);
        }
        return total / (x.size() - 1);
    }

    static double correlation(std::vector<double> x, std::vector<double> y) {
        return covariance(x, y) / (standardDeviation(x) * standardDeviation(y));
    }

    static double chebyshev(double k) {
        return 1 - 1 / (k * k);
    }

    static double weightedMean(std::vector<double> x, std::vector<double> y) { return 0.0; }

    static double geometricMean(std::vector<double> x) { return 0.0; }

    static double harmonicMean(std::vector<double> x) { return 0.0; }

    static double rms(std::vector<double> x) { return 0.0; }

    static double powerMean(std::vector<double> x, double k) { return 0.0; }

    static double lehmerMean(std::vector<double> x, double k) { return 0.0; }

    static double weightedLehmerMean(std::vector<double> x, std::vector<double> y, double k) { return 0.0; }

    static double contraHarmonicMean(std::vector<double> x) { return 0.0; }

    static double logMean(double x, double y) { return 0.0; }

    static double stolarskyMean(double x, double y, double z) { return 0.0; }
};

#endif  // STATISTICS_HPP