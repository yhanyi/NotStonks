#ifndef PORTFOLIOOPTIMIZATION_HPP
#define PORTFOLIOOPTIMIZATION_HPP

#include <vector>

class PortfolioOptimization {
   public:
    static std::vector<double> optimize(const std::vector<std::vector<double>>& returns, double risk_free_rate) {
        size_t num_assets = returns.size();
        std::vector<double> weights(num_assets, 1.0 / num_assets);  // initial equal weights

        // Implement a basic portfolio optimization algorithm, e.g., Mean-Variance Optimization
        double max_sharpe_ratio = -std::numeric_limits<double>::infinity();
        std::vector<double> best_weights;

        // This is a simplified example, proper optimization involves more complex methods
        for (size_t i = 0; i < num_assets; ++i) {
            weights[i] = 1.0;
            double portfolio_return = 0.0;
            double portfolio_variance = 0.0;

            for (size_t j = 0; j < num_assets; ++j) {
                portfolio_return += weights[j] * std::accumulate(returns[j].begin(), returns[j].end(), 0.0) / returns[j].size();
                for (size_t k = 0; k < num_assets; ++k) {
                    portfolio_variance += weights[j] * weights[k] * Analysis::covariance(returns[j], returns[k]);
                }
            }

            double sharpe_ratio = (portfolio_return - risk_free_rate) / std::sqrt(portfolio_variance);
            if (sharpe_ratio > max_sharpe_ratio) {
                max_sharpe_ratio = sharpe_ratio;
                best_weights = weights;
            }

            weights[i] = 0.0;
        }

        return best_weights;
    }
};

#endif  // PORTFOLIOOPTIMIZATION_HPP
