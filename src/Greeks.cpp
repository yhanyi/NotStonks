#include "Greeks.hpp"

#include <cmath>

double Greeks::norm_pdf(double x) {
    return (1.0 / (std::sqrt(2 * M_PI))) * std::exp(-0.5 * x * x);
}

double Greeks::norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

double Greeks::delta_call(double S, double K, double r, double sigma, double T) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return norm_cdf(d1);
}

double Greeks::delta_put(double S, double K, double r, double sigma, double T) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return norm_cdf(d1) - 1.0;
}

double Greeks::gamma(double S, double K, double r, double sigma, double T) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return norm_pdf(d1) / (S * sigma * std::sqrt(T));
}

double Greeks::vega(double S, double K, double r, double sigma, double T) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return S * norm_pdf(d1) * std::sqrt(T);
}

double Greeks::theta_call(double S, double K, double r, double sigma, double T) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return -(S * norm_pdf(d1) * sigma) / (2 * std::sqrt(T)) - r * K * std::exp(-r * T) * norm_cdf(d2);
}

double Greeks::theta_put(double S, double K, double r, double sigma, double T) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return -(S * norm_pdf(d1) * sigma) / (2 * std::sqrt(T)) + r * K * std::exp(-r * T) * norm_cdf(-d2);
}

double Greeks::rho_call(double S, double K, double r, double sigma, double T) {
    double d2 = (std::log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return K * T * std::exp(-r * T) * norm_cdf(d2);
}

double Greeks::rho_put(double S, double K, double r, double sigma, double T) {
    double d2 = (std::log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    return -K * T * std::exp(-r * T) * norm_cdf(-d2);
}
