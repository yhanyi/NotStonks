#include "Statistics.hpp"

#include <vector>

double Statistics::mean(std::vector<double> x) {
    double total = 0;
    for (int i = 0; i < x.size(); i++) {
        total += x[i];
    }
    return total / x.size();
}

double Statistics::median(std::vector<double> x) {
    sort(x.begin(), x.end());
    return (x.size() % 2) ? x[x.size() / 2 + 1] : mean({x[x.size() / 2 - 1], x[x.size() / 2]});
}

double Statistics::mode(std::vector<double> x) { ; }

double Statistics::standardDeviation(std::vector<double> x) {
    return std::sqrt(variance(x));
}

double Statistics::variance(std::vector<double> x) {
    double total = 0;
    double m = mean(x);
    for (int i = 0; i < x.size(); i++) {
        total += (x[i] - m) * (x[i] - m);
    }
    return total / (x.size() - 1);
}

double Statistics::covariance(std::vector<double> x, std::vector<double> y) {
    double total = 0;
    double m = mean(x), n = mean(y);
    for (int i = 0; i < x.size(); i++) {
        total += (x[i] - m) * (y[i] - n);
    }
    return total / (x.size() - 1);
}

double Statistics::correlation(std::vector<double> x, std::vector<double> y) {
    return covariance(x, y) / (standardDeviation(x) * standardDeviation(y));
}

double Statistics::chebyshev(double k) {
    return 1 - 1 / (k * k);
}

double Statistics::weightedMean(std::vector<double> x, std::vector<double> y) { return 0.0; }

double Statistics::geometricMean(std::vector<double> x) { return 0.0; }

double Statistics::harmonicMean(std::vector<double> x) { return 0.0; }

double Statistics::rms(std::vector<double> x) { return 0.0; }

double Statistics::powerMean(std::vector<double> x, double k) { return 0.0; }

double Statistics::lehmerMean(std::vector<double> x, double k) { return 0.0; }

double Statistics::weightedLehmerMean(std::vector<double> x, std::vector<double> y, double k) { return 0.0; }

double Statistics::contraHarmonicMean(std::vector<double> x) { return 0.0; }

double Statistics::logMean(double x, double y) { return 0.0; }

double Statistics::stolarskyMean(double x, double y, double z) { return 0.0; }