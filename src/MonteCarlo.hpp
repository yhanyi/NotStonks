#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <vector>

class MonteCarlo {
   public:
    static std::vector<double> simulate_price_path(double S0, double mu, double sigma, int num_steps, int num_simulations) {
        std::vector<double> price_path(num_steps);
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(mu / num_steps, sigma / sqrt(num_steps));

        for (int i = 0; i < num_simulations; ++i) {
            double S = S0;
            for (int j = 0; j < num_steps; ++j) {
                double dS = distribution(generator);
                S += S * dS;
                price_path[j] += S;
            }
        }

        for (double& price : price_path) {
            price /= num_simulations;
        }

        return price_path;
    }

    static double option_price(double S, double K, double r, double sigma, double T, int num_simulations, bool is_call) {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::normal_distribution<double> distribution(0.0, 1.0);

        double sum_payoff = 0.0;
        for (int i = 0; i < num_simulations; ++i) {
            double ST = S * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * distribution(generator));
            double payoff = is_call ? std::max(0.0, ST - K) : std::max(0.0, K - ST);
            sum_payoff += payoff;
        }

        double option_price = std::exp(-r * T) * sum_payoff / num_simulations;
        return option_price;
    }
};

#endif  // MONTECARLO_HPP
