#ifndef BINOMIALTREE_HPP
#define BINOMIALTREE_HPP

class BinomialTree {
   public:
    static double option_price(double S, double K, double r, double sigma, double T, int steps, bool is_call);
};

#endif  // BINOMIALTREE_HPP
