#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include <vector>

class LinearRegression {
   public:
    void fit(const std::vector<double>& x, const std::vector<double>& y);
    double predict(double x) const;

   private:
    double slope;
    double intercept;
};

#endif  // LINEARREGRESSION_HPP
