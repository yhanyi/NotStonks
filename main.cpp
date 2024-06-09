#include <iostream>
#include <vector>

#include "src/QuantLib.hpp"

int main() {
    try {
        FinancialData financial_data("datasets/test.csv");
        std::vector<double> closing_prices = financial_data.get_closing_prices();

        std::cout << "Mean Closing Price: " << Analysis::mean(closing_prices) << std::endl;
        std::cout << "Median Closing Price: " << Analysis::median(closing_prices) << std::endl;
        std::cout << "Standard Deviation of Closing Prices: " << Analysis::standard_deviation(closing_prices) << std::endl;

        int window_size = 20;
        std::vector<double> sma = Analysis::simple_moving_average(closing_prices, window_size);
        std::vector<double> ema = Analysis::exponential_moving_average(closing_prices, window_size);
        std::vector<double> bollinger_bands = Analysis::bollinger_bands(closing_prices, window_size);

        std::cout << "Simple Moving Average: ";
        for (double val : sma) std::cout << val << " ";
        std::cout << std::endl;

        std::cout << "Exponential Moving Average: ";
        for (double val : ema) std::cout << val << " ";
        std::cout << std::endl;

        std::cout << "Bollinger Bands: ";
        for (double val : bollinger_bands) std::cout << val << " ";
        std::cout << std::endl;

        std::vector<double> rsi = TechnicalIndicators::relative_strength_index(closing_prices, window_size);
        std::cout << "Relative Strength Index: ";
        for (double val : rsi) std::cout << val << " ";
        std::cout << std::endl;

        std::vector<double> macd_histogram = TechnicalIndicators::macd(closing_prices, 12, 26, 9);
        std::cout << "MACD Histogram: ";
        for (double val : macd_histogram) std::cout << val << " ";
        std::cout << std::endl;

        double S0 = 100.0, mu = 0.1, sigma = 0.2;
        int num_steps = 100, num_simulations = 1000;
        std::vector<double> price_path = MonteCarlo::simulate_price_path(S0, mu, sigma, num_steps, num_simulations);

        std::cout << "Monte Carlo Simulated Prices: ";
        for (double price : price_path) std::cout << price << " ";
        std::cout << std::endl;

        std::vector<std::vector<double>> returns = {closing_prices, closing_prices};  // Use actual returns data for realistic optimization
        double risk_free_rate = 0.02;
        std::vector<double> optimal_weights = PortfolioOptimization::optimize(returns, risk_free_rate);

        std::cout << "Optimal Portfolio Weights: ";
        for (double weight : optimal_weights) std::cout << weight << " ";
        std::cout << std::endl;

        double value_at_risk = RiskMetrics::value_at_risk(closing_prices, 0.95);
        std::cout << "Value at Risk: " << value_at_risk << std::endl;

        double conditional_value_at_risk = RiskMetrics::conditional_value_at_risk(closing_prices, 0.95);
        std::cout << "Conditional Value at Risk: " << conditional_value_at_risk << std::endl;

        double sharpe_ratio = RiskMetrics::sharpe_ratio(closing_prices, risk_free_rate);
        std::cout << "Sharpe Ratio: " << sharpe_ratio << std::endl;

        double backtest_result = Backtesting::run_backtest(closing_prices, "SMA");
        std::cout << "Backtest Result: " << backtest_result << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
