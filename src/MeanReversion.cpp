#include "MeanReversion.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <thread>

void MeanReversion::run() {
    while (brokerAPI.isRunning()) {
        trade();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MeanReversion::trade() {
    const std::vector<double>& prices = brokerAPI.getPrices();
    std::string logMessage;

    if (prices.size() < 20) {
        logMessage = "MeanReversion: Not enough data points to make a decision.";
        std::lock_guard<std::mutex> lock(logMutex);
        std::cout << logMessage << std::endl;
        return;
    }

    auto z_scores = calculate_z_score(prices, 20);
    auto signals = generate_signals(z_scores, 1.0, 0.5, 5);

    int lastSignal = signals.back();
    double currentPrice = prices.back();

    if (lastSignal == 1 && cash >= currentPrice) {
        int sharesToBuy = static_cast<int>(cash / currentPrice);
        brokerAPI.buy(sharesToBuy);
        cash -= sharesToBuy * currentPrice;
        shares += sharesToBuy;

        logMessage = "MeanReversion buys " + std::to_string(sharesToBuy) + " shares at " + std::to_string(currentPrice) + " price";
    } else if (lastSignal == -1 && shares > 0) {
        brokerAPI.sell(shares);
        cash += shares * currentPrice;

        logMessage = "MeanReversion sells " + std::to_string(shares) + " shares at " + std::to_string(currentPrice) + " price";
        shares = 0;
    } else {
        logMessage = "MeanReversion: No trade decision made.";
    }

    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << logMessage << std::endl;
}

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

double MeanReversion::backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash) {
    double portfolio_value = cash;
    int shares = 0;
    for (size_t i = 0; i < signals.size(); ++i) {
        if (signals[i] == 1 && cash >= prices[i]) {
            int sharesToBuy = static_cast<int>(cash / prices[i]);
            portfolio_value += sharesToBuy * (prices[i + 1] - prices[i]);
            shares += sharesToBuy;
            cash -= sharesToBuy * prices[i];
        } else if (signals[i] == -1 && shares > 0) {
            portfolio_value += shares * (prices[i + 1] - prices[i]);
            cash += shares * prices[i];
            shares = 0;
        }
        double current_value = cash + shares * prices[i];
        if (current_value / portfolio_value - 1 < -fixed_stop_loss_percentage) {
            portfolio_value = current_value;
            break;
        }
    }
    return portfolio_value;
}

void MeanReversion::optimize_parameters(const std::vector<double>& prices) {
    double best_portfolio_value = -std::numeric_limits<double>::infinity();
    int best_window_size = 20;
    double best_entry_threshold = 1.0;
    double best_exit_threshold = 0.5;
    int best_holding_period = 5;

    for (int window_size = 10; window_size <= 50; window_size += 10) {
        for (double entry_threshold = 0.5; entry_threshold <= 2.0; entry_threshold += 0.5) {
            for (double exit_threshold = 0.1; exit_threshold <= 1.0; exit_threshold += 0.1) {
                for (int holding_period = 5; holding_period <= 20; holding_period += 5) {
                    auto z_scores = calculate_z_score(prices, window_size);
                    auto signals = generate_signals(z_scores, entry_threshold, exit_threshold, holding_period);
                    double portfolio_value = backtest_strategy(signals, prices, 0.1, 0.2, 10000.0);
                    if (portfolio_value > best_portfolio_value) {
                        best_portfolio_value = portfolio_value;
                        best_window_size = window_size;
                        best_entry_threshold = entry_threshold;
                        best_exit_threshold = exit_threshold;
                        best_holding_period = holding_period;
                    }
                }
            }
        }
    }
    std::cout << "Best Parameters: " << "window_size=" << best_window_size
              << ", entry_threshold=" << best_entry_threshold
              << ", exit_threshold=" << best_exit_threshold
              << ", holding_period=" << best_holding_period << std::endl;
}
