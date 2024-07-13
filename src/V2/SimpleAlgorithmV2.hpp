#ifndef SIMPLEALGORITHMV2_HPP
#define SIMPLEALGORITHMV2_HPP

#include <thread>

#include "EngineV2.hpp"
#include "OrderbookV2.hpp"
#include "TradeAlgorithmV2.hpp"

class SimpleAlgorithmV2 : public TradeAlgorithmV2 {
   public:
    SimpleAlgorithmV2(int id, TradingEngine& engine, OrderbookV2& orderBook)
        : TradeAlgorithmV2(id, engine, orderBook) {}

    // void execute() override {
    //     std::lock_guard<std::mutex> lock(engine.priceMutex);  // Lock to ensure safe access to currentPrice
    //     double currentPrice = engine.getCurrentPrice();
    //     if (currentPrice < initialPrice && cash >= currentPrice) {
    //         int qty = static_cast<int>(cash / currentPrice);
    //         auto [transacted_qty, avg_price] = orderBook.execute_order(MARKET, qty, BUY);
    //         stocks += transacted_qty;
    //         cash -= transacted_qty * avg_price;
    //         std::cout << "Order executed: BUY " << transacted_qty << " @ " << avg_price << " by Algorithm " << id << std::endl;
    //     } else if (currentPrice > initialPrice && stocks > 0) {
    //         auto [transacted_qty, avg_price] = orderBook.execute_order(MARKET, stocks, SELL);
    //         stocks -= transacted_qty;
    //         cash += transacted_qty * avg_price;
    //         std::cout << "Order executed: SELL " << transacted_qty << " @ " << avg_price << " by Algorithm " << id << std::endl;
    //     }
    // }

    void execute() override {
        std::thread(&SimpleAlgorithmV2::trade, this).detach();
    }

    void trade() {
        while (true) {
            double currentPrice = engine.getCurrentPrice();
            if (currentPrice < initialPrice) {
                orderBook.add_order(10, currentPrice, BID);
                std::cout << "Added BID order for " << currentPrice << std::endl;
                auto [units, value] = orderBook.execute_order(MARKET, 10, BUY, currentPrice);
                stocks += units;
                cash -= value;
                std::cout << "Executed BUY order for " << currentPrice << std::endl;
            } else if (currentPrice > initialPrice) {
                orderBook.add_order(10, currentPrice, ASK);
                std::cout << "Added ASK order for " << currentPrice << std::endl;
                auto [units, value] = orderBook.execute_order(MARKET, 10, SELL, currentPrice);
                stocks -= units;
                cash += value;
                std::cout << "Executed SELL order for " << currentPrice << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

#endif  // SIMPLEALGORITHMV2_HPP