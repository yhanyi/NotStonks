#ifndef TRADEALGORITHMV2_HPP
#define TRADEALGORITHMV2_HPP

#include "EngineV2.hpp"
#include "OrderbookV2.hpp"

class TradeAlgorithmV2 {
   public:
    TradeAlgorithmV2(int id, TradingEngine& engine, OrderbookV2& orderBook)
        : id(id), engine(engine), orderBook(orderBook), initialPrice(engine.getCurrentPrice()), cash(10000), stocks(0) {}

    virtual void execute() = 0;
    void print_portfolio() {
        std::cout << "Algorithm " << id << " Portfolio:\n";
        std::cout << "Initial Price: " << initialPrice << "\n";
        std::cout << "Cash: " << cash << "\n";
        std::cout << "Stocks: " << stocks << "\n";
    }

    //  protected:
    int id;
    TradingEngine& engine;
    OrderbookV2& orderBook;
    double initialPrice;
    double cash;
    int stocks;
};

#endif  // TRADEALGORITHMV2_HPP
