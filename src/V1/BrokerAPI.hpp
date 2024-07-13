#ifndef BROKERAPI_HPP
#define BROKERAPI_HPP

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../FinancialData.hpp"

extern std::mutex logMutex;

class BrokerAPI {
   public:
    BrokerAPI() : running(false), duration(0) {
        std::srand(std::time(0));
        prices = {100.0};
    }

    ~BrokerAPI() {
        stopPriceGeneration();
    }

    bool isRunning() {
        return this->running;
    }

    void setDuration(int seconds) {
        duration = seconds;
    }

    void startPriceGeneration(int interval_ms) {
        if (running) return;  // Prevent multiple calls to start
        running = true;
        priceGenerationThread = std::thread([this, interval_ms]() {
            auto start = std::chrono::steady_clock::now();
            while (running) {
                generateNewPrice();
                std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() >= duration) {
                    running = false;
                }
            }
            reset();
        });
    }

    void stopPriceGeneration() {
        running = false;
        if (priceGenerationThread.joinable()) {
            priceGenerationThread.join();
        }
    }

    const std::vector<double>& getPrices() const {
        std::lock_guard<std::mutex> lock(mutex);
        return prices;
    }

    double getLatestPrice() const {
        std::lock_guard<std::mutex> lock(mutex);
        if (prices.empty()) {
            std::cerr << "Error: No prices available!" << std::endl;
            return 0.0;
        }
        return prices.back();
    }

    void buy(int shares) {
        std::lock_guard<std::mutex> lock(mutex);
        {
            std::lock_guard<std::mutex> logLock(logMutex);
            std::cout << "Buying " << shares << " shares." << std::endl;
        }
    }

    void sell(int shares) {
        std::lock_guard<std::mutex> lock(mutex);
        {
            std::lock_guard<std::mutex> logLock(logMutex);
            std::cout << "Selling " << shares << " shares." << std::endl;
        }
    }

    void loadPrices(const std::string& filename) {
        FinancialData data(filename);
        this->prices = data.get_closing_prices();
        std::cout << "Size: " << this->prices.size() << std::endl;
    }

    void reset() {
        std::lock_guard<std::mutex> lock(mutex);
        prices.clear();
    }

   private:
    void generateNewPrice() {
        double lastPrice = prices.back();
        double variation = ((std::rand() % 200) - 100) / 100.0;
        double newPrice = std::max(0.0, lastPrice + variation);
        {
            std::lock_guard<std::mutex> lock(mutex);
            prices.push_back(newPrice);
            if (prices.size() > 100) {
                prices.erase(prices.begin());
            }
        }
        {
            std::lock_guard<std::mutex> logLock(logMutex);
            std::cout << "New price generated: " << newPrice << "\n";
        }
    }

    std::vector<double> prices;
    std::thread priceGenerationThread;
    std::atomic<bool> running;
    int duration;
    mutable std::mutex mutex;
};

#endif  // BROKERAPI_HPP
