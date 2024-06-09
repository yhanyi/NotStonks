#include "MarketImpactModels.hpp"

double MarketImpactModels::calculate_price_impact(double order_quantity, double market_volume, double price_change) {
    return order_quantity * price_change / market_volume;
}

double MarketImpactModels::calculate_volume_impact(double order_quantity, double market_volume, double volume_change) {
    return order_quantity * volume_change / market_volume;
}
