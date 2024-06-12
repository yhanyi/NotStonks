#include "MeanReversion.hpp"

#include <cmath>
#include <iostream>
#include <numeric>

std::vector<double> MeanReversion::calculate_moving_average(const std::vector<double>& data, int window_size) {
    std::vector<double> moving_averages(data.size(), 0.0);
    double sum = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
        if (i >= window_size) {
            sum -= data[i - window_size];
            moving_averages[i] = sum / window_size;
        } else {
            moving_averages[i] = sum / (i + 1);
        }
    }
    return moving_averages;
}

std::vector<double> MeanReversion::calculate_standard_deviation(const std::vector<double>& data, int window_size) {
    std::vector<double> std_devs(data.size(), 0.0);
    auto moving_averages = MeanReversion::calculate_moving_average(data, window_size);
    for (size_t i = 0; i < data.size(); ++i) {
        if (i >= window_size - 1) {
            double sum = 0.0;
            for (size_t j = i + 1 - window_size; j <= i; ++j) {
                sum += std::pow(data[j] - moving_averages[i], 2);
            }
            std_devs[i] = std::sqrt(sum / window_size);
        }
    }
    return std_devs;
}

std::vector<double> MeanReversion::calculate_z_score(const std::vector<double>& data, int window_size) {
    auto moving_averages = MeanReversion::calculate_moving_average(data, window_size);
    auto std_devs = MeanReversion::calculate_standard_deviation(data, window_size);
    std::vector<double> z_scores(data.size(), 0.0);
    for (size_t i = 0; i < data.size(); ++i) {
        if (std_devs[i] != 0) {
            z_scores[i] = (data[i] - moving_averages[i]) / std_devs[i];
        }
    }
    return z_scores;
}

std::vector<int> MeanReversion::generate_signals(const std::vector<double>& z_scores, double entry_threshold, double exit_threshold, int holding_period) {
    std::vector<int> signals(z_scores.size(), 0);
    int hold_counter = 0;
    for (size_t i = 0; i < z_scores.size(); ++i) {
        if (hold_counter > 0) {
            --hold_counter;
            continue;
        }
        if (z_scores[i] > entry_threshold) {
            signals[i] = -1;  // Sell signal
            hold_counter = holding_period;
        } else if (z_scores[i] < -entry_threshold) {
            signals[i] = 1;  // Buy signal
            hold_counter = holding_period;
        } else if (std::abs(z_scores[i]) < exit_threshold) {
            signals[i] = 0;  // Close position
        }
    }
    return signals;
}

double MeanReversion::backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash = 10000.0) {
    double position = 0.0;             // Current position in stock
    double entry_price = 0.0;          // Entry price for current position
    double trailing_stop_price = 0.0;  // Trailing stop price
    double fixed_stop_price = 0.0;     // Fixed stop price

    for (size_t i = 0; i < signals.size(); ++i) {
        if (signals[i] == 1 && cash > 0) {  // Buy
            position = cash / prices[i];
            entry_price = prices[i];
            trailing_stop_price = entry_price * (1 - trailing_stop_loss_percentage);
            fixed_stop_price = entry_price * (1 - fixed_stop_loss_percentage);
            cash = 0;
        } else if (signals[i] == -1 && position > 0) {  // Sell
            cash = position * prices[i];
            position = 0;
        }

        // Update trailing stop price
        if (position > 0) {
            trailing_stop_price = std::max(trailing_stop_price, prices[i] * (1 - trailing_stop_loss_percentage));
            // Check if trailing stop or fixed stop is hit
            if (prices[i] < trailing_stop_price || prices[i] < fixed_stop_price) {
                cash = position * prices[i];
                position = 0;
            }
        }
    }

    return cash + position * prices.back();  // Final portfolio value
}

void MeanReversion::optimize_parameters(const std::vector<double>& prices) {
    double best_portfolio_value = 0.0;
    int best_moving_average_period = 20;
    double best_buy_threshold = 0.05;
    double best_sell_threshold = 0.05;
    double best_trailing_stop_loss_percentage = 0.05;
    double best_fixed_stop_loss_percentage = 0.1;

    for (int ma_period = 10; ma_period <= 50; ma_period += 10) {
        for (double buy_threshold = 0.02; buy_threshold <= 0.1; buy_threshold += 0.02) {
            for (double sell_threshold = 0.02; sell_threshold <= 0.1; sell_threshold += 0.02) {
                for (double trailing_stop_loss_percentage = 0.02; trailing_stop_loss_percentage <= 0.1; trailing_stop_loss_percentage += 0.02) {
                    for (double fixed_stop_loss_percentage = 0.05; fixed_stop_loss_percentage <= 0.2; fixed_stop_loss_percentage += 0.05) {
                        auto moving_average = MeanReversion::calculate_moving_average(prices, ma_period);
                        auto standard_deviations = MeanReversion::calculate_standard_deviation(prices, ma_period);
                        auto z_score = MeanReversion::calculate_z_score(prices, ma_period);
                        auto signals = MeanReversion::generate_signals(z_score, best_buy_threshold, best_sell_threshold, ma_period);
                        double portfolio_value = MeanReversion::backtest_strategy(signals, prices, trailing_stop_loss_percentage, fixed_stop_loss_percentage);

                        if (portfolio_value > best_portfolio_value) {
                            best_portfolio_value = portfolio_value;
                            best_moving_average_period = ma_period;
                            best_buy_threshold = buy_threshold;
                            best_sell_threshold = sell_threshold;
                            best_trailing_stop_loss_percentage = trailing_stop_loss_percentage;
                            best_fixed_stop_loss_percentage = fixed_stop_loss_percentage;
                        }
                    }
                }
            }
        }
    }

    std::cout << "Optimized Parameters: " << std::endl;
    std::cout << "Moving Average Period: " << best_moving_average_period << std::endl;
    std::cout << "Buy Threshold: " << best_buy_threshold << std::endl;
    std::cout << "Sell Threshold: " << best_sell_threshold << std::endl;
    std::cout << "Trailing Stop Loss Percentage: " << best_trailing_stop_loss_percentage << std::endl;
    std::cout << "Fixed Stop Loss Percentage: " << best_fixed_stop_loss_percentage << std::endl;
    std::cout << "Best Portfolio Value: " << best_portfolio_value << std::endl;
}