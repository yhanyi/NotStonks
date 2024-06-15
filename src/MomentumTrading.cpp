#include "MomentumTrading.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void MomentumTrading::run() {
    while (brokerAPI.isRunning()) {
        trade();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MomentumTrading::trade() {
    // double currentPrice = brokerAPI.getLatestPrice();
    // // Always buy if there's enough cash
    // if (cash >= currentPrice) {
    //     int sharesToBuy = 1;
    //     brokerAPI.buy(sharesToBuy);
    //     cash -= sharesToBuy * currentPrice;
    //     shares += sharesToBuy;
    //     std::cout << "MomentumTrading buys " << sharesToBuy << " shares at " << currentPrice << " price" << std::endl;
    // }
    // // Always sell if there are shares to sell
    // else if (shares > 0) {
    //     int sharesToSell = 1;
    //     brokerAPI.sell(sharesToSell);
    //     cash += sharesToSell * currentPrice;
    //     shares -= sharesToSell;
    //     std::cout << "MomentumTrading sells " << sharesToSell << " shares at " << currentPrice << " price" << std::endl;
    // }
    const std::vector<double>& prices = brokerAPI.getPrices();
    if (prices.size() < 15) return;  // Ensure we have enough data points

    auto rsi = calculate_rsi(prices, 14);
    auto signals = generate_signals(rsi, 30, 70);

    int lastSignal = signals.back();
    double currentPrice = prices.back();

    if (lastSignal == 1 && cash >= currentPrice) {
        int sharesToBuy = static_cast<int>(cash / currentPrice);
        brokerAPI.buy(sharesToBuy);
        cash -= sharesToBuy * currentPrice;
        shares += sharesToBuy;
        std::cout << "MomentumTrading buys " << sharesToBuy << " shares at " << currentPrice << " price" << std::endl;
    } else if (lastSignal == -1 && shares > 0) {
        int sharesToSell = shares;
        brokerAPI.sell(sharesToSell);
        cash += sharesToSell * currentPrice;
        shares -= sharesToSell;
        std::cout << "MomentumTrading sells " << sharesToSell << " shares at " << currentPrice << " price" << std::endl;
    }
}

std::vector<double> MomentumTrading::calculate_rsi(const std::vector<double>& prices, int period = 14) {
    std::vector<double> rsi;
    if (prices.size() <= period) return rsi;

    std::vector<double> gains, losses;
    for (size_t i = 1; i < prices.size(); ++i) {
        double change = prices[i] - prices[i - 1];
        if (change > 0)
            gains.push_back(change);
        else
            losses.push_back(-change);
    }

    double avg_gain = std::accumulate(gains.begin(), gains.begin() + period, 0.0) / period;
    double avg_loss = std::accumulate(losses.begin(), losses.begin() + period, 0.0) / period;

    for (size_t i = period; i < prices.size(); ++i) {
        if (i != period) {
            double change = prices[i] - prices[i - 1];
            avg_gain = (avg_gain * (period - 1) + (change > 0 ? change : 0)) / period;
            avg_loss = (avg_loss * (period - 1) + (change < 0 ? -change : 0)) / period;
        }

        double rs = avg_gain / avg_loss;
        rsi.push_back(100 - (100 / (1 + rs)));
    }

    return rsi;
}

std::vector<int> MomentumTrading::generate_signals(const std::vector<double>& rsi, double rsi_buy_threshold = 30.0, double rsi_sell_threshold = 70.0) {
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

double MomentumTrading::backtest_strategy(const std::vector<int>& signals, const std::vector<double>& prices, double trailing_stop_loss_percentage = 0.05, double fixed_stop_loss_percentage = 0.1, double cash = 10000.0) {
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

void MomentumTrading::optimize_parameters(const std::vector<double>& prices) {
    double best_portfolio_value = 0.0;
    int best_rsi_period = 14;
    double best_rsi_buy_threshold = 30.0;
    double best_rsi_sell_threshold = 70.0;
    double best_trailing_stop_loss_percentage = 0.05;
    double best_fixed_stop_loss_percentage = 0.1;

    for (int rsi_period = 10; rsi_period <= 20; ++rsi_period) {
        for (double rsi_buy_threshold = 20.0; rsi_buy_threshold <= 40.0; rsi_buy_threshold += 5.0) {
            for (double rsi_sell_threshold = 60.0; rsi_sell_threshold <= 80.0; rsi_sell_threshold += 5.0) {
                for (double trailing_stop_loss_percentage = 0.02; trailing_stop_loss_percentage <= 0.1; trailing_stop_loss_percentage += 0.02) {
                    for (double fixed_stop_loss_percentage = 0.05; fixed_stop_loss_percentage <= 0.15; fixed_stop_loss_percentage += 0.05) {
                        auto rsi = MomentumTrading::calculate_rsi(prices, rsi_period);
                        auto signals = MomentumTrading::generate_signals(rsi, rsi_buy_threshold, rsi_sell_threshold);
                        double portfolio_value = MomentumTrading::backtest_strategy(signals, prices, trailing_stop_loss_percentage, fixed_stop_loss_percentage);

                        if (portfolio_value > best_portfolio_value) {
                            best_portfolio_value = portfolio_value;
                            best_rsi_period = rsi_period;
                            best_rsi_buy_threshold = rsi_buy_threshold;
                            best_rsi_sell_threshold = rsi_sell_threshold;
                            best_trailing_stop_loss_percentage = trailing_stop_loss_percentage;
                            best_fixed_stop_loss_percentage = fixed_stop_loss_percentage;
                        }
                    }
                }
            }
        }
    }

    std::cout << "Optimized Parameters: " << std::endl;
    std::cout << "RSI Period: " << best_rsi_period << std::endl;
    std::cout << "RSI Buy Threshold: " << best_rsi_buy_threshold << std::endl;
    std::cout << "RSI Sell Threshold: " << best_rsi_sell_threshold << std::endl;
    std::cout << "Trailing Stop Loss Percentage: " << best_trailing_stop_loss_percentage << std::endl;
    std::cout << "Fixed Stop Loss Percentage: " << best_fixed_stop_loss_percentage << std::endl;
    std::cout << "Best Portfolio Value: " << best_portfolio_value << std::endl;
}
