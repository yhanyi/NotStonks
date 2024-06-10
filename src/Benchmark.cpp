#include "Benchmark.hpp"

#include <iostream>

Benchmark::Benchmark(const std::string& csv_file) : fd(csv_file) {}

std::map<std::string, double> Benchmark::evaluate_strategy(const std::vector<int>& signals) {
    std::vector<double> closing_prices = fd.get_closing_prices();
    double final_portfolio_value = EventDrivenBacktesting::simulate(closing_prices, signals, 10000, 1);
    std::vector<double> returns;
    for (size_t i = 1; i < closing_prices.size(); ++i) {
        returns.push_back((closing_prices[i] - closing_prices[i - 1]) / closing_prices[i - 1]);
    }
    double sharpe = RiskAdjustedPerformance::sharpe_ratio(returns, 0.001);

    return {{"Final Portfolio Value", final_portfolio_value}, {"Sharpe Ratio", sharpe}};
}

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
    std::vector<int> mean_reversion_signals = MeanReversion::generate_signals(closing_prices, 1.0);
    auto mean_reversion_results = evaluate_strategy(mean_reversion_signals);
    report_results(mean_reversion_results, "Mean Reversion");

    // Add more strategies here
    std::cout << "--------------------------- BENCHMARK END ---------------------------" << std::endl;
}
