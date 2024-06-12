#include "Benchmark.hpp"

#include <iostream>

#include "MeanReversion.hpp"
#include "QuantLib.hpp"

Benchmark::Benchmark(const std::string& csv_file) : fd(csv_file) {}

// std::map<std::string, double> Benchmark::evaluate_strategy(const std::vector<int>& signals) {
//     std::vector<double> closing_prices = fd.get_closing_prices();
//     double final_portfolio_value = EventDrivenBacktesting::simulate(closing_prices, signals, 10000, 1);
//     std::vector<double> returns;
//     for (size_t i = 1; i < closing_prices.size(); ++i) {
//         returns.push_back((closing_prices[i] - closing_prices[i - 1]) / closing_prices[i - 1]);
//     }
//     double sharpe = RiskAdjustedPerformance::sharpe_ratio(returns, 0.001);

//     return {{"Final Portfolio Value", final_portfolio_value}, {"Sharpe Ratio", sharpe}};
// }

void Benchmark::report_results(const std::map<std::string, double>& results, const std::string& strategy_name) {
    std::cout << "Results for " << strategy_name << " strategy:" << std::endl;
    for (const auto& result : results) {
        std::cout << result.first << ": " << result.second << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

void Benchmark::run() {
    std::cout << "-------------------------- BENCHMARK START --------------------------" << std::endl;
    std::vector<double> closing_prices = fd.get_closing_prices();

    // Mean Reversion Strategy
    // int window_size = 20;
    // double entry_threshold = 2.0;
    // double exit_threshold = 1.0;

    // auto z_scores = MeanReversion::calculate_z_score(closing_prices, window_size);
    // auto signals = MeanReversion::generate_signals(z_scores, entry_threshold, exit_threshold);
    // double final_portfolio_value = MeanReversion::backtest_strategy(signals, closing_prices, 10000);
    // std::cout << "Final Portfolio Value: " << final_portfolio_value << std::endl;

    // Add more strategies here
    std::cout << "--------------------------- BENCHMARK END ---------------------------" << std::endl;
}
