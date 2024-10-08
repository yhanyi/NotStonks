#ifndef BLACKSCHOLES_HPP
#define BLACKSCHOLES_HPP

#include <cmath>

class BlackScholes {
   public:
    static double call_price(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        return S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
    }

    static double put_price(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        return K * std::exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
    }

   private:
    static double norm_cdf(double x) {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }
};

#endif  // BLACKSCHOLES_HPP
