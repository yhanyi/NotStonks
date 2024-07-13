// DenseLayer_hpp

#ifndef DENSELAYER_HPP
#define DENSELAYER_HPP

#include <iostream>
#include <vector>

#include "ActivationFunctions.hpp"
#include "LinearAlgebra.hpp"

class DenseLayer {
   public:
    double (*activation_function)(const double &, const bool &);
    int neurons;
    std::string activation;
    std::vector<std::vector<double>> kernel;

    DenseLayer(const int &neurons, const std::string &activation, const std::pair<size_t, size_t> &kernel_shape, const bool &random_kernel) {
        setup_activation(activation);
        this->neurons = neurons;
        if (random_kernel) {
            kernel = LinearAlgebra::random_matrix<double>(kernel_shape.first, kernel_shape.second, -1.0, 1.0);
        } else {
            kernel = LinearAlgebra::unit_matrix<double>(kernel_shape.first, kernel_shape.second);
        }
    }

    DenseLayer(const int &neurons, const std::string &activation, const std::vector<std::vector<double>> &kernel) {
        setup_activation(activation);
        this->neurons = neurons;
        this->kernel = kernel;
    }

    DenseLayer(const DenseLayer &layer) = default;

    ~DenseLayer() = default;

    DenseLayer &operator=(const DenseLayer &layer) = default;

    DenseLayer(DenseLayer &&) = default;

    DenseLayer &operator=(DenseLayer &&) = default;

   private:
    void setup_activation(const std::string &activation) {
        if (activation == "sigmoid") {
            activation_function = ActivationFunctions::sigmoid;
        } else if (activation == "relu") {
            activation_function = ActivationFunctions::RELU;
        } else if (activation == "tanh") {
            activation_function = ActivationFunctions::tanh;
        } else if (activation == "none") {
            activation_function = ActivationFunctions::identity;
        } else {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid argument. Expected {none, sigmoid, relu, "
                         "tanh} got ";
            std::cerr << activation << std::endl;
            std::exit(EXIT_FAILURE);
        }
        this->activation = activation;
    }
};

#endif  // DENSELAYER_HPP