#ifndef MOMENTUMTRADING_HPP
#define MOMENTUMTRADING_HPP

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include "TradingAlgorithm.hpp"

class MomentumTrading : public TradingAlgorithm {
   public:
    MomentumTrading(BrokerAPI& api, std::mutex& logMutex, double cash, int shares) : TradingAlgorithm(api, logMutex, cash, shares) {}
    void run() override {
        while (brokerAPI.isRunning()) {
            trade();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Momentum Trading - Final Cash: " << cash << std::endl;
        std::cout << "Momentum Trading - Final Stocks: " << shares << std::endl;
    }
    void trade() override {
        const std::vector<double>& prices = brokerAPI.getPrices();
        std::string logMessage;

        if (prices.size() < 15) {
            logMessage = "MomentumTrading: Not enough data points to make a decision.";
            std::lock_guard<std::mutex> lock(logMutex);
            std::cout << logMessage << std::endl;
            return;
        }

        auto rsi = calculate_rsi(prices, 14);
        auto signals = generate_signals(rsi, 30, 70);

        int lastSignal = signals.back();
        double currentPrice = prices.back();

        if (lastSignal == 1 && cash >= currentPrice) {
            int sharesToBuy = static_cast<int>(cash / currentPrice);
            brokerAPI.buy(sharesToBuy);
            cash -= sharesToBuy * currentPrice;
            shares += sharesToBuy;

            logMessage = "MomentumTrading buys " + std::to_string(sharesToBuy) + " shares at " + std::to_string(currentPrice) + " price";
        } else if (lastSignal == -1 && shares > 0) {
            brokerAPI.sell(shares);
            cash += shares * currentPrice;

            logMessage = "MomentumTrading sells " + std::to_string(shares) + " shares at " + std::to_string(currentPrice) + " price";
            shares = 0;
        } else {
            logMessage = "MomentumTrading: No trade decision made.";
        }

        std::lock_guard<std::mutex> lock(logMutex);
        std::cout << logMessage << std::endl;
    }

   private:
    std::vector<double> calculate_rsi(const std::vector<double>& prices, int period) {
        std::vector<double> rsi(prices.size(), 0.0);
        if (prices.size() < period) {
            return rsi;
        }

        double avg_gain = 0.0;
        double avg_loss = 0.0;
        for (int i = 1; i <= period; ++i) {
            double change = prices[i] - prices[i - 1];
            if (change > 0) {
                avg_gain += change;
            } else {
                avg_loss -= change;
            }
        }
        avg_gain /= period;
        avg_loss /= period;

        rsi[period - 1] = 100 - (100 / (1 + (avg_gain / avg_loss)));

        for (size_t i = period; i < prices.size(); ++i) {
            double change = prices[i] - prices[i - 1];
            if (change > 0) {
                avg_gain = ((avg_gain * (period - 1)) + change) / period;
                avg_loss = (avg_loss * (period - 1)) / period;
            } else {
                avg_gain = (avg_gain * (period - 1)) / period;
                avg_loss = ((avg_loss * (period - 1)) - change) / period;
            }

            rsi[i] = 100 - (100 / (1 + (avg_gain / avg_loss)));
        }

        return rsi;
    }

    std::vector<int> generate_signals(const std::vector<double>& rsi, double rsi_buy_threshold, double rsi_sell_threshold) {
        std::vector<int> signals(rsi.size(), 0);
        for (size_t i = 0; i < rsi.size(); ++i) {
            if (rsi[i] < rsi_buy_threshold) {
                signals[i] = 1;  // Buy signal
            } else if (rsi[i] > rsi_sell_threshold) {
                signals[i] = -1;  // Sell signal
            }
        }
        return signals;
    }

    double backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage, double fixed_stop_loss_percentage, double cash) {
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

    void optimize_parameters(const std::vector<double>& prices) {
        double best_portfolio_value = -std::numeric_limits<double>::infinity();
        int best_period = 14;
        double best_rsi_buy_threshold = 30.0;
        double best_rsi_sell_threshold = 70.0;

        for (int period = 10; period <= 20; period += 2) {
            for (double rsi_buy_threshold = 20.0; rsi_buy_threshold <= 40.0; rsi_buy_threshold += 5.0) {
                for (double rsi_sell_threshold = 60.0; rsi_sell_threshold <= 80.0; rsi_sell_threshold += 5.0) {
                    auto rsi = calculate_rsi(prices, period);
                    auto signals = generate_signals(rsi, rsi_buy_threshold, rsi_sell_threshold);
                    double portfolio_value = backtest_strategy(signals, prices, 0.1, 0.2, 10000.0);
                    if (portfolio_value > best_portfolio_value) {
                        best_portfolio_value = portfolio_value;
                        best_period = period;
                        best_rsi_buy_threshold = rsi_buy_threshold;
                        best_rsi_sell_threshold = rsi_sell_threshold;
                    }
                }
            }
        }
        std::cout << "Best Parameters: " << "period=" << best_period
                  << ", rsi_buy_threshold=" << best_rsi_buy_threshold
                  << ", rsi_sell_threshold=" << best_rsi_sell_threshold << std::endl;
    }
};

#endif  // MOMENTUMTRADING_HPP
