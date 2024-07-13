// Utilities.hpp

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <tuple>
#include <vector>

class Utilities {
   public:
    template <typename T>
    static double performance(std::vector<T> y, std::vector<T> y_hat) {
        double total = 0;
        for (int i = 0; i < y.size(); i++) {
            if (std::round(y[i]) == y_hat[i]) {
                total++;
            }
        }
        return total / y.size();
    }

    template <typename T>
    static double performance(std::vector<std::vector<T>> y, std::vector<std::vector<T>> y_hat) {
        double total = 0;
        for (int i = 0; i < y.size(); i++) {
            double sub_total = 0;
            for (int j = 0; j < y[0].size(); j++) {
                if (std::round(y[i][j] == y_hat[i][j])) {
                    sub_total++;
                }
                if (sub_total == y_hat[0].size()) {
                    total++;
                }
            }
        }
        return total / y.size();
    }

    template <typename T>
    static std::tuple<double, double, double, double> confusionMatrix(std::vector<T> y, std::vector<T> y_hat) {
        double TP, FP, TN, FN = 0;
        for (int i = 0; i < y.size(); i++) {
            if (y[i] == y_hat[i]) {
                if (y_hat[i] == 1) {
                    TP++;
                } else {
                    TN++;
                }
            } else {
                if (y_hat[i] == 1) {
                    FP++;
                } else {
                    FN++;
                }
            }
        }
        return {TP, FP, TN, FN};
    }

    template <typename T>
    static double recall(std::vector<T> y, std::vector<T> y_hat) {
        auto [TP, FP, TN, FN] = confusionMatrix(y, y_hat);
        return TP / (TP + FN);
    }

    template <typename T>
    static double precision(std::vector<T> y, std::vector<T> y_hat) {
        auto [TP, FP, TN, FN] = confusionMatrix(y, y_hat);
        return TP / (TP + FP);
    }

    template <typename T>
    static double accuracy(std::vector<T> y, std::vector<T> y_hat) {
        auto [TP, FP, TN, FN] = confusionMatrix(y, y_hat);
        return (TP + TN) / (TP + FP + FN + TN);
    }

    template <typename T>
    static double f1Score(std::vector<T> y, std::vector<T> y_hat) {
        return 2 * precision(y, y_hat) * recall(y, y_hat) / (precision(y, y_hat) + recall(y, y_hat));
    }
};

#endif  // UTILITIES_HPP