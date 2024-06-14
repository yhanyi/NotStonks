#include "AutomaticDifferentiation.hpp"

Variable::Variable(double value, double grad) : value_(value), grad_(grad) {}

double Variable::value() const {
    return value_;
}

double Variable::grad() const {
    return grad_;
}

void Variable::set_grad(double grad) {
    grad_ = grad;
}

Variable Variable::operator+(const Variable& other) const {
    return Variable(value_ + other.value_, grad_ + other.grad_);
}

Variable Variable::operator*(const Variable& other) const {
    return Variable(value_ * other.value_, value_ * other.grad_ + grad_ * other.value_);
}