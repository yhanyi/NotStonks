#ifndef AUTOMATICDIFFERENTIATION_HPP
#define AUTOMATICDIFFERENTIATION_HPP

class Variable {
   public:
    Variable(double value, double grad = 0.0);
    double value() const;
    double grad() const;
    void set_grad(double grad);
    Variable operator+(const Variable& other) const;
    Variable operator*(const Variable& other) const;

   private:
    double value_;
    double grad_;
};
#endif  // AUTOMATICDIFFERENTIATION_HPP
