#ifndef ENGINEV2_HPP
#define ENGINEV2_HPP

#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "EnumsV2.hpp"

class TradingEngine {
   public:
    TradingEngine(const std::vector<double>& historicalPrices, int duration, SimulationMethod method)
        : historicalPrices(historicalPrices), duration(duration), currentIndex(0), method(method) {
        std::random_device rd;
        generator.seed(rd());
        distribution = std::normal_distribution<>(0, 1);
        currentPrice = historicalPrices.back();
    }

    void start() {
        std::thread(&TradingEngine::generatePrices, this).detach();
    }

    double getCurrentPrice() {
        std::lock_guard<std::mutex> lock(priceMutex);
        return currentPrice;
    }

    void generatePrices() {
        for (int i = 0; i < duration; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            switch (method) {
                case RANDOM_WALK:
                    randomWalk();
                    break;
                case BLACK_SCHOLES:
                    blackScholes();
                    break;
                case MONTE_CARLO:
                    monteCarlo();
                    break;
            }
            std::lock_guard<std::mutex> lock(priceMutex);
            std::cout << "Generated Price: " << currentPrice << std::endl;
        }
    }

    void randomWalk() {
        double change = distribution(generator);
        currentPrice *= (1 + change / 100);
    }

    void blackScholes() {
        double S = currentPrice;
        double K = historicalPrices.front();  // Example strike price
        double r = 0.01;                      // Example risk-free rate
        double sigma = 0.2;                   // Example volatility
        double T = 1.0 / 252.0;               // One trading day
        double d1 = (std::log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        currentPrice = S * std::exp((r - sigma * sigma / 2) * T + sigma * std::sqrt(T) * distribution(generator));
    }

    void monteCarlo() {
        double S = currentPrice;
        double r = 0.01;         // Example risk-free rate
        double sigma = 0.2;      // Example volatility
        double T = 1.0 / 252.0;  // One trading day
        int numSimulations = 100;
        double sum = 0.0;

        for (int i = 0; i < numSimulations; ++i) {
            double St = S * std::exp((r - sigma * sigma / 2) * T + sigma * std::sqrt(T) * distribution(generator));
            sum += St;
        }

        currentPrice = sum / numSimulations;
    }

    std::vector<double> historicalPrices;
    int duration;
    double currentPrice;
    int currentIndex;
    std::default_random_engine generator;
    std::normal_distribution<> distribution;
    std::mutex priceMutex;
    SimulationMethod method;
};

#endif  // ENGINEV2_HPP