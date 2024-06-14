#ifndef BLACKSCHOLES_HPP
#define BLACKSCHOLES_HPP

class BlackScholes {
   public:
    static double call_price(double S, double K, double r, double sigma, double T);
    static double put_price(double S, double K, double r, double sigma, double T);

   private:
    static double norm_cdf(double x);
};

#endif  // BLACKSCHOLES_HPP
