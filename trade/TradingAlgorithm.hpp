// TradingAlgorithm.hpp
#ifndef TRADINGALGORITHM_HPP
#define TRADINGALGORITHM_HPP

#include "BrokerAPI.hpp"

class TradingAlgorithm {
   protected:
    BrokerAPI& brokerAPI;

   public:
    TradingAlgorithm(BrokerAPI& api) : brokerAPI(api) {}
    virtual void run() = 0;
};

#endif  // TRADINGALGORITHM_HPP
