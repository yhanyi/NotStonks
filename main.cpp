#include <iostream>
#include <string>
#include <vector>

#include "ml/MLCPP.hpp"
#include "quant/QuantLib.hpp"

int main() {
    try {
        // Create a .csv dataset and return the filename for computation.
        std::string filename;
        filename = "datasets/finance/" + cli();

        FinancialData financial_data(filename);
        std::vector<double> closing_prices = financial_data.get_closing_prices();
        std::vector<double> market_returns = financial_data.get_closing_prices();  // Use real market data

        // std::cout << "Mean Closing Price: " << Analysis::mean(closing_prices) << std::endl;
        // std::cout << "Median Closing Price: " << Analysis::median(closing_prices) << std::endl;
        // std::cout << "Standard Deviation of Closing Prices: " << Analysis::standard_deviation(closing_prices) << std::endl;

        // int window_size = 20;
        // std::vector<double> sma = Analysis::simple_moving_average(closing_prices, window_size);
        // std::vector<double> ema = Analysis::exponential_moving_average(closing_prices, window_size);
        // std::vector<double> bollinger_bands = Analysis::bollinger_bands(closing_prices, window_size);

        // std::cout << "Simple Moving Average: ";
        // for (double val : sma) std::cout << val << " ";
        // std::cout << std::endl;

        // std::cout << "Exponential Moving Average: ";
        // for (double val : ema) std::cout << val << " ";
        // std::cout << std::endl;

        // std::cout << "Bollinger Bands: ";
        // for (double val : bollinger_bands) std::cout << val << " ";
        // std::cout << std::endl;

        // std::vector<double> rsi = TechnicalIndicators::relative_strength_index(closing_prices, window_size);
        // std::cout << "Relative Strength Index: ";
        // for (double val : rsi) std::cout << val << " ";
        // std::cout << std::endl;

        // std::vector<double> macd_histogram = TechnicalIndicators::macd(closing_prices, 12, 26, 9);
        // std::cout << "MACD Histogram: ";
        // for (double val : macd_histogram) std::cout << val << " ";
        // std::cout << std::endl;

        // double S0 = 100.0, mu = 0.1, sigma = 0.2;
        // int num_steps = 100, num_simulations = 1000;
        // std::vector<double> price_path = MonteCarlo::simulate_price_path(S0, mu, sigma, num_steps, num_simulations);

        // std::cout << "Monte Carlo Simulated Prices: ";
        // for (double price : price_path) std::cout << price << " ";
        // std::cout << std::endl;

        // std::vector<std::vector<double>> returns = {closing_prices, closing_prices};  // Use actual returns data for realistic optimization
        // double risk_free_rate = 0.02;
        // std::vector<double> optimal_weights = PortfolioOptimization::optimize(returns, risk_free_rate);

        // std::cout << "Optimal Portfolio Weights: ";
        // for (double weight : optimal_weights) std::cout << weight << " ";
        // std::cout << std::endl;

        // double value_at_risk = RiskMetrics::value_at_risk(closing_prices, 0.95);
        // std::cout << "Value at Risk: " << value_at_risk << std::endl;

        // double conditional_value_at_risk = RiskMetrics::conditional_value_at_risk(closing_prices, 0.95);
        // std::cout << "Conditional Value at Risk: " << conditional_value_at_risk << std::endl;

        // double sharpe_ratio = RiskMetrics::sharpe_ratio(closing_prices, risk_free_rate);
        // std::cout << "Sharpe Ratio: " << sharpe_ratio << std::endl;

        // double backtest_result = Backtesting::run_backtest(closing_prices, "SMA");
        // std::cout << "Backtest Result: " << backtest_result << std::endl;

        // double S = 100.0, K = 105.0, r = 0.05, T = 1.0;
        // double call_price = BlackScholes::call_price(S, K, r, sigma, T);
        // double put_price = BlackScholes::put_price(S, K, r, sigma, T);
        // std::cout << "Black-Scholes Call Price: " << call_price << std::endl;
        // std::cout << "Black-Scholes Put Price: " << put_price << std::endl;

        // // Pairs Trading
        // std::vector<double> prices1 = closing_prices;
        // std::vector<double> prices2 = closing_prices;
        // auto [mean_spread, std_dev_spread] = PairsTrading::calculate_spread(prices1, prices2);
        // std::cout << "Mean Spread: " << mean_spread << ", Std Dev Spread: " << std_dev_spread << std::endl;

        // std::vector<double> spread = Analysis::simple_moving_average(prices1, window_size);  // Example spread calculation
        // auto [long_signals, short_signals] = PairsTrading::generate_signals(spread, 2 * std_dev_spread, std_dev_spread);
        // std::cout << "Long Signals: ";
        // for (double signal : long_signals) std::cout << signal << " ";
        // std::cout << std::endl;
        // std::cout << "Short Signals: ";
        // for (double signal : short_signals) std::cout << signal << " ";
        // std::cout << std::endl;

        // // Event Study
        // std::vector<double> abnormal_returns = EventStudy::calculate_abnormal_returns(closing_prices, market_returns);
        // double car = EventStudy::cumulative_abnormal_return(abnormal_returns);
        // std::cout << "Cumulative Abnormal Return: " << car << std::endl;

        // // Greeks Calculation
        // double deltaC = Greeks::delta_call(S, K, r, sigma, T);
        // double deltaP = Greeks::delta_put(S, K, r, sigma, T);
        // double gamma = Greeks::gamma(S, K, r, sigma, T);
        // double vega = Greeks::vega(S, K, r, sigma, T);
        // double thetaC = Greeks::theta_call(S, K, r, sigma, T);
        // double thetaP = Greeks::theta_put(S, K, r, sigma, T);
        // double rhoC = Greeks::rho_call(S, K, r, sigma, T);
        // double rhoP = Greeks::rho_put(S, K, r, sigma, T);

        // std::cout << "Delta (Call): " << deltaC << std::endl;
        // std::cout << "Delta (Put): " << deltaP << std::endl;
        // std::cout << "Gamma: " << gamma << std::endl;
        // std::cout << "Vega: " << vega << std::endl;
        // std::cout << "Theta (Call): " << thetaC << std::endl;
        // std::cout << "Theta (Put): " << thetaP << std::endl;
        // std::cout << "Rho (Call): " << rhoC << std::endl;
        // std::cout << "Rho (Put): " << rhoP << std::endl;

        // // High-Frequency Trading Metrics
        // OrderBook order_book;
        // order_book.add_order(100.5, 100, true);
        // order_book.add_order(101.5, 200, true);
        // order_book.add_order(102.5, 300, false);
        // order_book.add_order(103.5, 400, false);

        // auto best_bid_ask = order_book.get_best_bid_ask();
        // std::cout << "Best Bid: " << best_bid_ask.first << ", Best Ask: " << best_bid_ask.second << std::endl;

        // // Advanced Time Series Analysis
        // std::vector<double> arima_result = ARIMA::fit(closing_prices, 1, 1, 1);
        // std::cout << "ARIMA Result: ";
        // for (double val : arima_result) {
        //     std::cout << val << " ";
        // }
        // std::cout << std::endl;

        // // Machine Learning for Trading
        // std::vector<double> x = {1, 2, 3, 4, 5};
        // std::vector<double> y = {1, 2, 3, 4, 5};
        // LinearRegression lr;
        // lr.fit(x, y);
        // std::cout << "Linear Regression Prediction for x=6: " << lr.predict(6) << std::endl;

        // // Risk Management
        // double stress_test_result = RiskManagement::stress_test(closing_prices, 1.5);
        // std::cout << "Stress Test Result: " << stress_test_result << std::endl;

        // // Advanced Option Pricing
        // S = 100;              // Underlying asset price
        // K = 100;              // Strike price
        // r = 0.05;             // Risk-free rate
        // sigma = 0.2;          // Volatility
        // T = 1;                // Time to maturity
        // int steps = 100;      // Number of steps in binomial tree
        // bool is_call = true;  // Call option

        // double binomial_price = BinomialTree::option_price(S, K, r, sigma, T, steps, is_call);
        // std::cout << "Binomial Tree Option Price: " << binomial_price << std::endl;

        // // Auto-Correlation
        // std::vector<double> autocorr = AutoCorrelation::calculate(closing_prices, 5);
        // std::cout << "Auto-Correlation: ";
        // for (const auto& ac : autocorr) {
        //     std::cout << ac << " ";
        // }
        // std::cout << std::endl;

        // // Risk-Adjusted Performance
        // std::vector<double> returns2 = {0.01, 0.02, -0.01, 0.03, 0.01};
        // double sharpe = RiskAdjustedPerformance::sharpe_ratio(returns2, 0.001);
        // std::cout << "Sharpe Ratio: " << sharpe << std::endl;

        // // ARIMA model
        // std::vector<double> arima_result2 = ARIMA::fit(closing_prices, 1, 1, 1);
        // std::cout << "ARIMA Model Output: ";
        // for (const auto& val : arima_result2) {
        //     std::cout << val << " ";
        // }
        // std::cout << std::endl;

        // // Liquidity Metrics
        // std::vector<int> volumes = {1000, 1200, 1500, 1300, 1100};
        // std::cout << "Amihud Illiquidity: " << LiquidityMetrics::calculate_amihud(closing_prices, volumes) << std::endl;

        // // Execution Algorithms
        // std::vector<double> vwap_prices = ExecutionAlgorithms::vwap(closing_prices, volumes);
        // std::cout << "VWAP Prices: ";
        // for (const auto& price : vwap_prices) {
        //     std::cout << price << " ";
        // }
        // std::cout << std::endl;

        // // Realized Volatility
        // std::vector<double> intraday_prices = {100, 102, 101, 103, 105, 104};  // Example intraday prices
        // double realized_volatility = RealizedVolatility::calculate(intraday_prices);
        // std::cout << "Realized Volatility: " << realized_volatility << std::endl;

        // // Transaction Cost Analysis
        // double total_cost = TransactionCostAnalysis::calculate_total_cost(closing_prices, volumes, 0.001);
        // std::cout << "Total Transaction Cost: " << total_cost << std::endl;

        // Strategy Testing

        // Mean Reversion Strategy
        int window_size = 20;
        double entry_threshold = 2.0;
        double exit_threshold = 1.0;
        int holding_period = 7;
        double cash = 10000.0;
        double trailing_stop_loss_percentage = 0.05;
        double fixed_stop_loss_percentage = 0.1;
        double final_portfolio_value;

        auto z_scores = MeanReversion::calculate_z_score(closing_prices, window_size);
        auto signals = MeanReversion::generate_signals(z_scores, entry_threshold, exit_threshold, holding_period);
        final_portfolio_value = MeanReversion::backtest_strategy(signals, closing_prices, trailing_stop_loss_percentage, fixed_stop_loss_percentage, cash);
        std::cout << "Mean Reversion - Final Portfolio Value: " << final_portfolio_value << std::endl;
        std::cout << "Mean Reversion - Optimal Parameters" << std::endl;
        MeanReversion::optimize_parameters(closing_prices);

        // Momentum Trading Strategy
        int rsi_period = 14;
        double rsi_buy_threshold = 30.0;
        double rsi_sell_threshold = 70.0;

        auto rsi = MomentumTrading::calculate_rsi(closing_prices, rsi_period);
        signals = MomentumTrading::generate_signals(rsi, rsi_buy_threshold, rsi_sell_threshold);
        final_portfolio_value = MomentumTrading::backtest_strategy(signals, closing_prices, trailing_stop_loss_percentage, fixed_stop_loss_percentage, cash);
        std::cout << "Momentum Trading - Final Portfolio Value: " << final_portfolio_value << std::endl;

        std::cout << "Momentum Trading - Optimal Parameters" << std::endl;
        MomentumTrading::optimize_parameters(closing_prices);

        // // Event-Driven Backtesting
        // double final_portfolio_value = EventDrivenBacktesting::simulate(closing_prices, signals, 10000, 1);
        // std::cout << "Final Portfolio Value: " << final_portfolio_value << std::endl;

        // Benchmarking Functionality
        // Benchmark benchmark(filename);
        // benchmark.run();

        // Clear the datasets folder before ending the program.
        clean();

        MLCPP::NeuralNetwork nn = MLCPP::NeuralNetwork({{4, "none"}, {6, "relu"}, {3, "sigmoid"}});
        nn.summary();
        nn.fit_from_csv("datasets/iris.csv", true, 100, 0.3, false, 2, 32, true);
        assert(MLCPP::LinearAlgebra::argmax(nn.single_predict({{5, 3.4, 1.6, 0.4}})) == 0);
        assert(MLCPP::LinearAlgebra::argmax(nn.single_predict({{6.4, 2.9, 4.3, 1.3}})) == 1);
        assert(MLCPP::LinearAlgebra::argmax(nn.single_predict({{6.2, 3.4, 5.4, 2.3}})) == 2);
        nn.save_model("test");

        // Gradient Descent Example
        MLCPP::GradientDescent gd(0.01);
        std::vector<double> weights = {0.5, 0.3};
        std::vector<double> gradients = {0.1, 0.2};
        gd.update(weights, gradients);
        std::cout << "Updated weights (GD): " << weights[0] << ", " << weights[1] << std::endl;

        // Adam Optimizer Example
        MLCPP::AdamOptimizer adam(0.001, 0.9, 0.999, 1e-8);
        std::vector<double> weights_adam = {0.5, 0.3};
        std::vector<double> gradients_adam = {0.1, 0.2};
        adam.update(weights_adam, gradients_adam);
        std::cout << "Updated weights (Adam): " << weights_adam[0] << ", " << weights_adam[1] << std::endl;

        // Automatic Differentiation Example
        MLCPP::Variable x(2.0);
        MLCPP::Variable y(3.0);
        MLCPP::Variable z = x * y + x;
        z.set_grad(1.0);
        std::cout << "Value of z: " << z.value() << ", Gradient of z: " << z.grad() << std::endl;

        // Sparse Matrix Example
        MLCPP::SparseMatrix sm1(3, 3);
        MLCPP::SparseMatrix sm2(3, 3);
        sm1.addValue(0, 0, 1.0);
        sm1.addValue(1, 1, 2.0);
        sm1.addValue(2, 2, 3.0);
        sm2.addValue(0, 0, 4.0);
        sm2.addValue(1, 1, 5.0);
        sm2.addValue(2, 2, 6.0);
        MLCPP::SparseMatrix result = sm1.multiply(sm2);
        std::cout << "Sparse Matrix Multiplication Result (0,0): " << result.getValue(0, 0) << std::endl;

        // Convolution Example
        MLCPP::Convolution conv;
        std::vector<std::vector<double>> input = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        std::vector<std::vector<double>> kernel = {{1, 0}, {0, -1}};
        auto conv_result = conv.convolve(input, kernel);
        std::cout << "Convolution Result (1,1): " << conv_result[1][1] << std::endl;

        // Pooling Example
        MLCPP::Pooling pool;
        auto pooled_result = pool.pool(input, 2, MLCPP::Pooling::PoolingType::MAX);
        std::cout << "Pooling Result (0,0): " << pooled_result[0][0] << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
