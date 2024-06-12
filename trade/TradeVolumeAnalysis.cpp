#include "TradeVolumeAnalysis.hpp"

#include <numeric>

double TradeVolumeAnalysis::calculate_volume_weighted_average_price(const std::vector<double>& prices, const std::vector<int>& volumes) {
    double total_volume = 0;
    double weighted_sum = 0;
    for (size_t i = 0; i < prices.size(); ++i) {
        total_volume += volumes[i];
        weighted_sum += prices[i] * volumes[i];
    }
    return weighted_sum / total_volume;
}

double TradeVolumeAnalysis::calculate_volume_participation_ratio(const std::vector<int>& volumes) {
    int max_volume = *std::max_element(volumes.begin(), volumes.end());
    double total_volume = std::accumulate(volumes.begin(), volumes.end(), 0);
    return static_cast<double>(max_volume) / total_volume;
}
