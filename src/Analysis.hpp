#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

class Analysis {
   public:
    static double mean(const std::vector<double>& data) {
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    static double median(std::vector<double> data) {
        size_t size = data.size();
        std::sort(data.begin(), data.end());
        if (size % 2 == 0) {
            return (data[size / 2 - 1] + data[size / 2]) / 2;
        } else {
            return data[size / 2];
        }
    }

    static double variance(const std::vector<double>& data) {
        double mean_value = mean(data);
        double sum = 0.0;
        for (double value : data) {
            sum += (value - mean_value) * (value - mean_value);
        }
        return sum / (data.size() - 1);
    }

    static double standard_deviation(const std::vector<double>& data) {
        return std::sqrt(variance(data));
    }

    static double covariance(const std::vector<double>& data1, const std::vector<double>& data2) {
        double mean1 = mean(data1);
        double mean2 = mean(data2);
        double covariance = 0.0;
        for (size_t i = 0; i < data1.size(); ++i) {
            covariance += (data1[i] - mean1) * (data2[i] - mean2);
        }
        return covariance / (data1.size() - 1);
    }

    static double correlation(const std::vector<double>& data1, const std::vector<double>& data2) {
        double cov = covariance(data1, data2);
        double stddev1 = standard_deviation(data1);
        double stddev2 = standard_deviation(data2);
        return cov / (stddev1 * stddev2);
    }

    static std::vector<double> simple_moving_average(const std::vector<double>& data, int window_size) {
        std::vector<double> sma;
        double sum = 0.0;
        for (size_t i = 0; i < data.size(); ++i) {
            sum += data[i];
            if (i >= window_size) {
                sum -= data[i - window_size];
            }
            if (i >= window_size - 1) {
                sma.push_back(sum / window_size);
            }
        }
        return sma;
    }

    static std::vector<double> exponential_moving_average(const std::vector<double>& data, int window_size) {
        std::vector<double> ema;
        double multiplier = 2.0 / (window_size + 1);
        ema.push_back(data[0]);
        for (size_t i = 1; i < data.size(); ++i) {
            double value = (data[i] - ema.back()) * multiplier + ema.back();
            ema.push_back(value);
        }
        return ema;
    }

    static std::vector<double> bollinger_bands(const std::vector<double>& data, int window_size) {
        std::vector<double> bands;
        std::vector<double> sma = simple_moving_average(data, window_size);
        std::vector<double> std_dev;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i >= window_size - 1) {
                std::vector<double> window(data.begin() + i - window_size + 1, data.begin() + i + 1);
                std_dev.push_back(standard_deviation(window));
            }
        }
        for (size_t i = 0; i < sma.size(); ++i) {
            bands.push_back(sma[i] + 2 * std_dev[i]);
            bands.push_back(sma[i] - 2 * std_dev[i]);
        }
        return bands;
    }
};

#endif  // ANALYSIS_HPP
