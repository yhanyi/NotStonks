#include <iostream>
#include <string>
#include <vector>

#include "src/QuantLib.hpp"

int main() {
    try {
        // Create a .csv dataset and return the filename for computation.
        std::string filename;
        filename = "datasets/" + cli();
        std::cout << filename << std::endl;

        FinancialData financial_data(filename);
        std::vector<double> closing_prices = financial_data.get_closing_prices();
        std::vector<double> market_returns = financial_data.get_closing_prices();  // Use real market data

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

        double S = 100.0, K = 105.0, r = 0.05, T = 1.0;
        double call_price = BlackScholes::call_price(S, K, r, sigma, T);
        double put_price = BlackScholes::put_price(S, K, r, sigma, T);
        std::cout << "Black-Scholes Call Price: " << call_price << std::endl;
        std::cout << "Black-Scholes Put Price: " << put_price << std::endl;

        // Pairs Trading
        std::vector<double> prices1 = closing_prices;
        std::vector<double> prices2 = closing_prices;
        auto [mean_spread, std_dev_spread] = PairsTrading::calculate_spread(prices1, prices2);
        std::cout << "Mean Spread: " << mean_spread << ", Std Dev Spread: " << std_dev_spread << std::endl;

        std::vector<double> spread = Analysis::simple_moving_average(prices1, window_size);  // Example spread calculation
        auto [long_signals, short_signals] = PairsTrading::generate_signals(spread, 2 * std_dev_spread, std_dev_spread);
        std::cout << "Long Signals: ";
        for (double signal : long_signals) std::cout << signal << " ";
        std::cout << std::endl;
        std::cout << "Short Signals: ";
        for (double signal : short_signals) std::cout << signal << " ";
        std::cout << std::endl;

        // Event Study
        std::vector<double> abnormal_returns = EventStudy::calculate_abnormal_returns(closing_prices, market_returns);
        double car = EventStudy::cumulative_abnormal_return(abnormal_returns);
        std::cout << "Cumulative Abnormal Return: " << car << std::endl;

        // Greeks Calculation
        double deltaC = Greeks::delta_call(S, K, r, sigma, T);
        double deltaP = Greeks::delta_put(S, K, r, sigma, T);
        double gamma = Greeks::gamma(S, K, r, sigma, T);
        double vega = Greeks::vega(S, K, r, sigma, T);
        double thetaC = Greeks::theta_call(S, K, r, sigma, T);
        double thetaP = Greeks::theta_put(S, K, r, sigma, T);
        double rhoC = Greeks::rho_call(S, K, r, sigma, T);
        double rhoP = Greeks::rho_put(S, K, r, sigma, T);

        std::cout << "Delta (Call): " << deltaC << std::endl;
        std::cout << "Delta (Put): " << deltaP << std::endl;
        std::cout << "Gamma: " << gamma << std::endl;
        std::cout << "Vega: " << vega << std::endl;
        std::cout << "Theta (Call): " << thetaC << std::endl;
        std::cout << "Theta (Put): " << thetaP << std::endl;
        std::cout << "Rho (Call): " << rhoC << std::endl;
        std::cout << "Rho (Put): " << rhoP << std::endl;

        // High-Frequency Trading Metrics
        OrderBook order_book;
        order_book.add_order(100.5, 100, true);
        order_book.add_order(101.5, 200, true);
        order_book.add_order(102.5, 300, false);
        order_book.add_order(103.5, 400, false);

        auto best_bid_ask = order_book.get_best_bid_ask();
        std::cout << "Best Bid: " << best_bid_ask.first << ", Best Ask: " << best_bid_ask.second << std::endl;

        // Advanced Time Series Analysis
        std::vector<double> arima_result = ARIMA::fit(closing_prices, 1, 1, 1);
        std::cout << "ARIMA Result: ";
        for (double val : arima_result) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Machine Learning for Trading
        std::vector<double> x = {1, 2, 3, 4, 5};
        std::vector<double> y = {1, 2, 3, 4, 5};
        LinearRegression lr;
        lr.fit(x, y);
        std::cout << "Linear Regression Prediction for x=6: " << lr.predict(6) << std::endl;

        // Risk Management
        double stress_test_result = RiskManagement::stress_test(closing_prices, 1.5);
        std::cout << "Stress Test Result: " << stress_test_result << std::endl;

        // Advanced Option Pricing
        S = 100;              // Underlying asset price
        K = 100;              // Strike price
        r = 0.05;             // Risk-free rate
        sigma = 0.2;          // Volatility
        T = 1;                // Time to maturity
        int steps = 100;      // Number of steps in binomial tree
        bool is_call = true;  // Call option

        double binomial_price = BinomialTree::option_price(S, K, r, sigma, T, steps, is_call);
        std::cout << "Binomial Tree Option Price: " << binomial_price << std::endl;

        // Auto-Correlation
        std::vector<double> autocorr = AutoCorrelation::calculate(closing_prices, 5);
        std::cout << "Auto-Correlation: ";
        for (const auto& ac : autocorr) {
            std::cout << ac << " ";
        }
        std::cout << std::endl;

        // Risk-Adjusted Performance
        std::vector<double> returns2 = {0.01, 0.02, -0.01, 0.03, 0.01};
        double sharpe = RiskAdjustedPerformance::sharpe_ratio(returns2, 0.001);
        std::cout << "Sharpe Ratio: " << sharpe << std::endl;

        // ARIMA model
        std::vector<double> arima_result2 = ARIMA::fit(closing_prices, 1, 1, 1);
        std::cout << "ARIMA Model Output: ";
        for (const auto& val : arima_result2) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Liquidity Metrics
        std::vector<int> volumes = {1000, 1200, 1500, 1300, 1100};
        std::cout << "Amihud Illiquidity: " << LiquidityMetrics::calculate_amihud(closing_prices, volumes) << std::endl;

        // Execution Algorithms
        std::vector<double> vwap_prices = ExecutionAlgorithms::vwap(closing_prices, volumes);
        std::cout << "VWAP Prices: ";
        for (const auto& price : vwap_prices) {
            std::cout << price << " ";
        }
        std::cout << std::endl;

        // Realized Volatility
        std::vector<double> intraday_prices = {100, 102, 101, 103, 105, 104};  // Example intraday prices
        double realized_volatility = RealizedVolatility::calculate(intraday_prices);
        std::cout << "Realized Volatility: " << realized_volatility << std::endl;

        // Transaction Cost Analysis
        double total_cost = TransactionCostAnalysis::calculate_total_cost(closing_prices, volumes, 0.001);
        std::cout << "Total Transaction Cost: " << total_cost << std::endl;

        // Mean Reversion Strategy
        std::vector<int> signals = MeanReversion::generate_signals(closing_prices, 1.0);
        std::cout << "Mean Reversion Signals: ";
        for (const auto& signal : signals) {
            std::cout << signal << " ";
        }
        std::cout << std::endl;

        // Event-Driven Backtesting
        double final_portfolio_value = EventDrivenBacktesting::simulate(closing_prices, signals, 10000, 1);
        std::cout << "Final Portfolio Value: " << final_portfolio_value << std::endl;

        // Benchmarking Functionality
        Benchmark benchmark(filename);
        benchmark.run();

        // Clear the datasets folder before ending the program.
        clean();

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
