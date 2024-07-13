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

    void add_order(double price, int quantity, bool is_buy) {
        if (is_buy) {
            buy_orders[price] += quantity;
        } else {
            sell_orders[price] += quantity;
        }
    }

    void remove_order(double price, int quantity, bool is_buy) {
        if (is_buy) {
            if (buy_orders.count(price)) {
                buy_orders[price] -= quantity;
                if (buy_orders[price] <= 0) {
                    buy_orders.erase(price);
                }
            }
        } else {
            if (sell_orders.count(price)) {
                sell_orders[price] -= quantity;
                if (sell_orders[price] <= 0) {
                    sell_orders.erase(price);
                }
            }
        }
    }

    std::pair<double, double> get_best_bid_ask() const {
        double best_bid = buy_orders.empty() ? 0.0 : buy_orders.rbegin()->first;
        double best_ask = sell_orders.empty() ? 0.0 : sell_orders.begin()->first;
        return {best_bid, best_ask};
    }

    double get_market_depth(double price) const {
        double depth = 0;
        for (const auto& order : buy_orders) {
            if (order.first >= price) break;
            depth += order.second;
        }
        for (const auto& order : sell_orders) {
            if (order.first <= price) break;
            depth += order.second;
        }
        return depth;
    }

   private:
    std::map<double, int> buy_orders;
    std::map<double, int> sell_orders;
};

#endif  // ORDERBOOK_HPP
