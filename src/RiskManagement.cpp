#include "RiskManagement.hpp"

double RiskManagement::stress_test(const std::vector<double>& portfolio_returns, double stress_factor) {
    double stressed_value = 0.0;
    for (double return_val : portfolio_returns) {
        stressed_value += return_val * stress_factor;
    }
    return stressed_value;
}
