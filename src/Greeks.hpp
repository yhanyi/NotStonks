#ifndef GREEKS_HPP
#define GREEKS_HPP

class Greeks {
   public:
    static double delta_call(double S, double K, double r, double sigma, double T);
    static double delta_put(double S, double K, double r, double sigma, double T);
    static double gamma(double S, double K, double r, double sigma, double T);
    static double vega(double S, double K, double r, double sigma, double T);
    static double theta_call(double S, double K, double r, double sigma, double T);
    static double theta_put(double S, double K, double r, double sigma, double T);
    static double rho_call(double S, double K, double r, double sigma, double T);
    static double rho_put(double S, double K, double r, double sigma, double T);

   private:
    static double norm_pdf(double x);
    static double norm_cdf(double x);
};

#endif  // GREEKS_HPP
