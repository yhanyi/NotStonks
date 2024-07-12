#ifndef GREEKS_HPP
#define GREEKS_HPP

#include <cmath>
class Greeks {
   public:
    static double delta_call(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        return norm_cdf(d1);
    }

    static double delta_put(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        return norm_cdf(d1) - 1.0;
    }

    static double gamma(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        return norm_pdf(d1) / (S * sigma * std::sqrt(T));
    }

    static double vega(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        return S * norm_pdf(d1) * std::sqrt(T);
    }

    static double theta_call(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        return -(S * norm_pdf(d1) * sigma) / (2 * std::sqrt(T)) - r * K * std::exp(-r * T) * norm_cdf(d2);
    }

    static double theta_put(double S, double K, double r, double sigma, double T) {
        double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        double d2 = d1 - sigma * std::sqrt(T);
        return -(S * norm_pdf(d1) * sigma) / (2 * std::sqrt(T)) + r * K * std::exp(-r * T) * norm_cdf(-d2);
    }

    static double rho_call(double S, double K, double r, double sigma, double T) {
        double d2 = (std::log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        return K * T * std::exp(-r * T) * norm_cdf(d2);
    }

    static double rho_put(double S, double K, double r, double sigma, double T) {
        double d2 = (std::log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        return -K * T * std::exp(-r * T) * norm_cdf(-d2);
    }

   private:
    static double norm_pdf(double x) {
        return (1.0 / (std::sqrt(2 * M_PI))) * std::exp(-0.5 * x * x);
    }

    static double norm_cdf(double x) {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }
};

#endif  // GREEKS_HPP
