// Utilities.hpp

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <tuple>
#include <vector>

class Utilities {
   public:
    template <typename T>
    static double performance(std::vector<T> y, std::vector<T> y_hat);

    template <typename T>
    static double performance(std::vector<std::vector<T>> y, std::vector<std::vector<T>> y_hat);

    template <typename T>
    static std::tuple<double, double, double, double> confusionMatrix(std::vector<T> y, std::vector<T> y_hat);

    template <typename T>
    static double recall(std::vector<T> y, std::vector<T> y_hat);

    template <typename T>
    static double precision(std::vector<T> y, std::vector<T> y_hat);

    template <typename T>
    static double accuracy(std::vector<T> y, std::vector<T> y_hat);

    template <typename T>
    static double f1Score(std::vector<T> y, std::vector<T> y_hat);
};

#endif  // UTILITIES_HPP