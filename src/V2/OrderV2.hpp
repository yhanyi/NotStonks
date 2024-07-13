#ifndef ORDERV2_HPP
#define ORDERV2_HPP

#include <stdlib.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <vector>

#include "EnumsV2.hpp"

inline uint64_t unix_time() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

class Order {
    int quantity;
    double price;
    BookSide side;
    uint64_t timestamp;

   public:
    Order(int quantity_, double price_, BookSide side_) {
        timestamp = unix_time();
        quantity = quantity_;
        price = price_;
        side = side_;
    }

    void set_quantity(int new_qty) { quantity = new_qty; }
    int get_quantity() { return quantity; }
    double get_price() { return price; }
    time_t get_timestamp() { return timestamp; }
};

#endif  // ORDERV2_HPP