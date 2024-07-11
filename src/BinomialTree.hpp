#ifndef BINOMIALTREE_HPP
#define BINOMIALTREE_HPP

#include <algorithm>
#include <cmath>
#include <vector>

class BinomialTree {
   public:
    static double option_price(double S, double K, double r, double sigma, double T, int steps, bool is_call) {
        double dt = T / steps;
        double u = std::exp(sigma * std::sqrt(dt));
        double d = 1 / u;
        double p = (std::exp(r * dt) - d) / (u - d);

        std::vector<double> prices(steps + 1);
        std::vector<double> option_values(steps + 1);

        for (int i = 0; i <= steps; ++i) {
            prices[i] = S * std::pow(u, steps - i) * std::pow(d, i);
            option_values[i] = std::max(0.0, (is_call ? prices[i] - K : K - prices[i]));
        }

        for (int step = steps - 1; step >= 0; --step) {
            for (int i = 0; i <= step; ++i) {
                option_values[i] = (p * option_values[i] + (1 - p) * option_values[i + 1]) * std::exp(-r * dt);
            }
        }

        return option_values[0];
    }
};

#endif  // BINOMIALTREE_HPP
