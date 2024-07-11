#ifndef EQUITYPRICEGENERATOR_HPP
#define EQUITYPRICEGENERATOR_HPP

#include <random>
#include <vector>
using std::mt19937_64;

class EquityPriceGenerator {
   public:
    std::vector<double> operator()(int seed) const {
        std::vector<double> v;
        mt19937_64 mtEngine(seed);
        std::normal_distribution<> nd;
        auto newPrice = [this](double previousEquityPrice, double norm) {
            double price = 0.0;
            double expArg1 = (rfRate_ - ((volatility_ * volatility_) / 2.0)) * dt_;
            double expArg2 = volatility_ * norm * sqrt(dt_);
            price = previousEquityPrice * std::exp(expArg1 + expArg2);
            return price;
        };
        v.push_back(initEquityPrice_);
        double equityPrice = initEquityPrice_;
        for (int i = 1; i <= numTimeSteps_; i++) {
            equityPrice = newPrice(equityPrice, nd(mtEngine));
            v.push_back(equityPrice);
        }
        return v;
    }

   private:
    double rfRate_;
    double volatility_;
    double dt_;
    double initEquityPrice_;
    int numTimeSteps_;
};

#endif  // EQUITYPRICEGENERATOR_HPP