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

        int window_size = 5;
        std::vector<double> sma = Analysis::simple_moving_average(closing_prices, window_size);
        std::cout << "Simple Moving Average (5-day): ";
        for (double value : sma) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
