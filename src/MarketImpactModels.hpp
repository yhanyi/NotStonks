#ifndef MARKETIMPACTMODELS_HPP
#define MARKETIMPACTMODELS_HPP

class MarketImpactModels {
   public:
    static double calculate_price_impact(double order_quantity, double market_volume, double price_change);
    static double calculate_volume_impact(double order_quantity, double market_volume, double volume_change);
};

#endif  // MARKETIMPACTMODELS_HPP
