// TradingAlgorithm.hpp
#ifndef TRADINGALGORITHM_HPP
#define TRADINGALGORITHM_HPP

#include "BrokerAPI.hpp"

class TradingAlgorithm {
   protected:
    BrokerAPI& brokerAPI;
    double cash;
    int shares;

   public:
    TradingAlgorithm(BrokerAPI& api, double cash, int shares) : brokerAPI(api), cash(cash), shares(shares) {}
    virtual void run() = 0;
    virtual void trade() = 0;
    double calculate_portfolio_value() const {
        double latest_price = brokerAPI.getLatestPrice();
        return cash + shares * latest_price;
    }
};

#endif  // TRADINGALGORITHM_HPP
