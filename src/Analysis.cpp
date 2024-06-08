#include "Analysis.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

double Analysis::mean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double Analysis::median(std::vector<double> data) {
    size_t size = data.size();
    std::sort(data.begin(), data.end());
    if (size % 2 == 0) {
        return (data[size / 2 - 1] + data[size / 2]) / 2;
    } else {
        return data[size / 2];
    }
}

double Analysis::variance(const std::vector<double>& data) {
    double mean_value = mean(data);
    double sum = 0.0;
    for (double value : data) {
        sum += (value - mean_value) * (value - mean_value);
    }
    return sum / (data.size() - 1);
}

double Analysis::standard_deviation(const std::vector<double>& data) {
    return std::sqrt(variance(data));
}

std::vector<double> Analysis::simple_moving_average(const std::vector<double>& data, int window_size) {
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

std::vector<double> Analysis::exponential_moving_average(const std::vector<double>& data, int window_size) {
    std::vector<double> ema;
    double multiplier = 2.0 / (window_size + 1);
    ema.push_back(data[0]);
    for (size_t i = 1; i < data.size(); ++i) {
        double value = (data[i] - ema.back()) * multiplier + ema.back();
        ema.push_back(value);
    }
    return ema;
}
