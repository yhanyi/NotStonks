#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include <numeric>
#include <vector>

class LinearRegression {
   public:
    void fit(const std::vector<double>& x, const std::vector<double>& y) {
        double x_mean = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
        double y_mean = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

        double numerator = 0.0;
        double denominator = 0.0;

        for (size_t i = 0; i < x.size(); ++i) {
            numerator += (x[i] - x_mean) * (y[i] - y_mean);
            denominator += (x[i] - x_mean) * (x[i] - x_mean);
        }

        slope = numerator / denominator;
        intercept = y_mean - slope * x_mean;
    }
    double predict(double x) const {
        return intercept + slope * x;
    }

   private:
    double slope;
    double intercept;
};

#endif  // LINEARREGRESSION_HPP
