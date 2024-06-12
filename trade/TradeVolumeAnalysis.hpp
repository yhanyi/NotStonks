#ifndef TRADEVOLUMEANALYSIS_HPP
#define TRADEVOLUMEANALYSIS_HPP

#include <vector>

class TradeVolumeAnalysis {
   public:
    static double calculate_volume_weighted_average_price(const std::vector<double>& prices, const std::vector<int>& volumes);
    static double calculate_volume_participation_ratio(const std::vector<int>& volumes);
};

#endif  // TRADEVOLUMEANALYSIS_HPP
