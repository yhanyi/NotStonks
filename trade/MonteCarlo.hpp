#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <vector>

class MonteCarlo {
   public:
    static std::vector<double> simulate_price_path(double S0, double mu, double sigma, int num_steps, int num_simulations);
    static double option_price(double S, double K, double r, double sigma, double T, int num_simulations, bool is_call);
};

#endif  // MONTECARLO_HPP
