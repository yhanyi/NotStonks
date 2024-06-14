#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <map>
#include <vector>

class OrderBook {
   public:
    struct Order {
        double price;
        int quantity;
        bool is_buy;
    };

    void add_order(double price, int quantity, bool is_buy);
    void remove_order(double price, int quantity, bool is_buy);
    std::pair<double, double> get_best_bid_ask() const;
    double get_market_depth(double price) const;

   private:
    std::map<double, int> buy_orders;
    std::map<double, int> sell_orders;
};

#endif  // ORDERBOOK_HPP
