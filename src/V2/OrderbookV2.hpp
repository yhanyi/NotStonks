#ifndef ORDERBOOKV2_HPP
#define ORDERBOOKV2_HPP

#include <stdlib.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <tuple>
#include <vector>

#include "EnumsV2.hpp"
#include "OrderV2.hpp"

class OrderbookV2 {
   public:
    OrderbookV2() {
        srand(time(NULL));

        // Add some dummy orders
        for (int i = 0; i < 10; i++) {
            double random_price = 105.0 + (rand() % 1001) / 100.0;
            int random_qty = rand() % 100 + 1;
            int random_qty2 = rand() % 100 + 1;

            add_order(random_qty, random_price, BID);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Sleep for a millisecond so the orders have different timestamps
            add_order(random_qty2, random_price, BID);
        }
        for (int i = 0; i < 10; i++) {
            double random_price = 110.0 + (rand() % 1001) / 100.0;
            int random_qty = rand() % 100 + 1;
            int random_qty2 = rand() % 100 + 1;

            add_order(random_qty, random_price, ASK);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Sleep for a millisecond so the orders have different timestamps
            add_order(random_qty2, random_price, ASK);
        }
    }

    void add_order(int qty, double price, BookSide side) {
        if (side == BID) {
            bids[price].push_back(std::make_unique<Order>(qty, price, side));
        } else {
            asks[price].push_back(std::make_unique<Order>(qty, price, side));
        }
    }

    std::tuple<int, double> execute_order(OrderType type, int order_quantity, Side side, double price = 0) {
        int units_transacted = 0;
        double total_value = 0;

        auto process = [&](auto& offers, Side side) {
            for (auto rit = offers.rbegin(); rit != offers.rend();) {
                auto& pair = *rit;  // Dereference iterator to get the key-value pair
                double price_level = pair.first;

                auto& quotes = pair.second;  // Order vector

                // Sort quotes in ascending order by timestamp
                std::sort(quotes.begin(), quotes.end(), [](const std::unique_ptr<Order>& a, const std::unique_ptr<Order>& b) {
                    return a->get_timestamp() < b->get_timestamp();
                });

                // Ensure agreeable price for limit order
                bool can_transact = true;
                if (type == LIMIT) {
                    if (side == BUY && price_level > price) {
                        can_transact = false;
                    } else if (side == SELL && price_level < price) {
                        can_transact = false;
                    }
                }

                // lift/hit as many levels as needed until qty filled
                auto it = quotes.begin();
                while (it != quotes.end() && order_quantity > 0 && can_transact) {
                    int quote_qty = (*it)->get_quantity();
                    uint64_t timestamp = (*it)->get_timestamp();
                    if (quote_qty > order_quantity) {
                        units_transacted += order_quantity;
                        total_value += order_quantity * pair.first;

                        // Fill part of this order and break
                        (*it)->set_quantity(quote_qty - order_quantity);
                        quote_qty -= order_quantity;
                        order_quantity = 0;
                        break;
                    } else {
                        units_transacted += quote_qty;
                        total_value += quote_qty * price_level;

                        // delete order from book and on
                        order_quantity -= quote_qty;
                        it = quotes.erase(it);
                    }
                }
                rit++;
            }
            remove_empty_keys();
            return std::make_tuple(units_transacted, total_value);
        };

        // market order
        if (type == MARKET) {
            return (side == SELL) ? process(bids, SELL) : process(asks, BUY);
        } else if (type == LIMIT) {
            // Analytics
            int units_transacted = 0;
            double total_value = 0;

            if (side == BUY) {
                if (best_quote(ASK) <= price) {
                    // Can at least partially fill
                    std::tuple<int, double> fill = process(asks, BUY);
                    // Add remaining order to book
                    add_order(order_quantity, price, BID);
                    return fill;
                } else {
                    // No fill possible, put on book
                    add_order(order_quantity, price, BID);
                    return std::make_tuple(units_transacted, total_value);
                }
            } else {
                if (best_quote(BID) >= price) {
                    // Can at least partially fill
                    std::tuple<int, double> fill = process(bids, SELL);
                    // Add remaining order to book
                    add_order(order_quantity, price, ASK);
                    return fill;
                } else {
                    // No fill possible, put on book
                    add_order(order_quantity, price, ASK);
                    return std::make_tuple(units_transacted, total_value);
                }
            }
        } else {
            throw std::runtime_error("Invalid order type encountered");
        }
    }

    double best_quote(BookSide side) {
        if (side == BID && !bids.empty()) {
            return std::prev(bids.end())->first;
        } else if (side == ASK && !asks.empty()) {
            return std::prev(asks.end())->first;
        } else {
            return 0.0;  // Default value if no quotes are available
        }
    }

    void print() {
        std::cout << "========== Orderbook =========" << std::endl;
        print_leg(asks, BookSide::ASK);

        // print bid-ask spread
        double best_ask = best_quote(BookSide::ASK);
        double best_bid = best_quote(BookSide::BID);
        std::cout << "\n\033[1;33m" << "======  " << 10000 * (best_ask - best_bid) / best_bid << "bps  ======\033[0m\n\n";

        print_leg(bids, BookSide::BID);
        std::cout << "==============================\n\n\n";
    }

   private:
    std::map<double, std::vector<std::unique_ptr<Order>>, std::greater<double>> asks;
    std::map<double, std::vector<std::unique_ptr<Order>>, std::less<double>> bids;

    template <typename T>
    void clean_leg(std::map<double, std::vector<std::unique_ptr<Order>>, T>& map) {
        for (auto it = map.begin(); it != map.end();) {
            if (it->second.empty()) {  // Check if the vector associated with the current key is empty
                it = map.erase(it);    // Erase the key and update the iterator to the next element
            } else {
                ++it;  // Move to the next element
            }
        }
    }

    void remove_empty_keys() {
        // Remove all empty keys from map
        clean_leg(bids);
        clean_leg(asks);
    }

    template <typename T>
    void print_leg(std::map<double, std::vector<std::unique_ptr<Order>>, T>& hashmap, BookSide side) {
        if (side == ASK) {
            for (auto& pair : hashmap) {  // Price level
                // Count size at a price level
                int size_sum = 0;
                for (auto& order : pair.second) {  // Order level
                    size_sum += order->get_quantity();
                }

                std::string color = "31";
                std::cout << "\t\033[1;" << color << "m" << "$" << std::setw(6) << std::fixed << std::setprecision(2) << pair.first << std::setw(5) << size_sum << "\033[0m ";

                // Make bars to visualize size
                for (int i = 0; i < size_sum / 10; i++) {
                    std::cout << "█";
                }
                std::cout << std::endl;
            }
        } else if (side == BID) {
            for (auto pair = hashmap.rbegin(); pair != hashmap.rend(); ++pair) {  // Price level
                int size_sum = 0;
                for (auto& order : pair->second) {  // Order level
                    size_sum += order->get_quantity();
                }

                std::string color = "32";
                std::cout << "\t\033[1;" << color << "m" << "$" << std::setw(6) << std::fixed << std::setprecision(2) << pair->first << std::setw(5) << size_sum << "\033[0m ";

                // Make bars to visualize size
                for (int i = 0; i < size_sum / 10; i++) {
                    std::cout << "█";
                }
                std::cout << std::endl;
            }
        }
    }
};

#endif  // ORDERBOOKV2_HPP