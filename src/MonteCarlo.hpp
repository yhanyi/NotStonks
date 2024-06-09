#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include <vector>

class MonteCarlo {
   public:
    static std::vector<double> simulate_price_path(double S0, double mu, double sigma, int num_steps, int num_simulations);
};

#endif  // MONTECARLO_HPP
