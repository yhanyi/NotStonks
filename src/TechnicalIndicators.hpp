#ifndef TECHNICALINDICATORS_HPP
#define TECHNICALINDICATORS_HPP

#include <vector>

class TechnicalIndicators {
   public:
    static std::vector<double> relative_strength_index(const std::vector<double>& data, int window_size) {
        std::vector<double> rsi(data.size(), 0.0);
        if (data.size() < window_size) return rsi;

        std::vector<double> gains(window_size, 0.0);
        std::vector<double> losses(window_size, 0.0);

        for (size_t i = 1; i < window_size; ++i) {
            double change = data[i] - data[i - 1];
            if (change > 0)
                gains[i] = change;
            else
                losses[i] = -change;
        }

        double avg_gain = std::accumulate(gains.begin(), gains.end(), 0.0) / window_size;
        double avg_loss = std::accumulate(losses.begin(), losses.end(), 0.0) / window_size;

        for (size_t i = window_size; i < data.size(); ++i) {
            double change = data[i] - data[i - 1];
            if (change > 0) {
                avg_gain = (avg_gain * (window_size - 1) + change) / window_size;
                avg_loss = (avg_loss * (window_size - 1)) / window_size;
            } else {
                avg_gain = (avg_gain * (window_size - 1)) / window_size;
                avg_loss = (avg_loss * (window_size - 1) - change) / window_size;
            }

            double rs = avg_gain / avg_loss;
            rsi[i] = 100 - (100 / (1 + rs));
        }

        return rsi;
    }

    static std::vector<double> macd(const std::vector<double>& data, int short_window, int long_window, int signal_window) {
        std::vector<double> macd_line(data.size(), 0.0);
        std::vector<double> signal_line(data.size(), 0.0);
        std::vector<double> macd_histogram(data.size(), 0.0);

        std::vector<double> short_ema = Analysis::exponential_moving_average(data, short_window);
        std::vector<double> long_ema = Analysis::exponential_moving_average(data, long_window);

        for (size_t i = 0; i < data.size(); ++i) {
            macd_line[i] = short_ema[i] - long_ema[i];
        }

        signal_line = Analysis::exponential_moving_average(macd_line, signal_window);

        for (size_t i = 0; i < data.size(); ++i) {
            macd_histogram[i] = macd_line[i] - signal_line[i];
        }

        return macd_histogram;
    }
};

#endif  // TECHNICALINDICATORS_HPP
