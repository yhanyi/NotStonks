#include "MonteCarlo.hpp"

#include <cmath>
#include <random>

std::vector<double> MonteCarlo::simulate_price_path(double S0, double mu, double sigma, int num_steps, int num_simulations) {
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
