#include "ExecutionAlgorithms.hpp"

#include <numeric>

std::vector<double> ExecutionAlgorithms::vwap(const std::vector<double>& prices, const std::vector<int>& volumes) {
    std::vector<double> vwap_prices;
    double cumulative_price_volume = 0.0;
    double cumulative_volume = 0.0;

    for (size_t i = 0; i < prices.size(); ++i) {
        cumulative_price_volume += prices[i] * volumes[i];
        cumulative_volume += volumes[i];
        vwap_prices.push_back(cumulative_price_volume / cumulative_volume);
    }

    return vwap_prices;
}

std::vector<double> ExecutionAlgorithms::twap(const std::vector<double>& prices, int n) {
    std::vector<double> twap_prices;
    double cumulative_price = 0.0;

    for (size_t i = 0; i < prices.size(); ++i) {
        cumulative_price += prices[i];
        if ((i + 1) % n == 0) {
            twap_prices.push_back(cumulative_price / n);
            cumulative_price = 0.0;
        }
    }

    return twap_prices;
}
