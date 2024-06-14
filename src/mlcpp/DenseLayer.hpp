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

    DenseLayer(const int &neurons, const std::string &activation, const std::pair<size_t, size_t> &kernel_shape, const bool &random_kernel);

    DenseLayer(const int &neurons, const std::string &activation, const std::vector<std::vector<double>> &kernel);

    DenseLayer(const DenseLayer &layer);

    ~DenseLayer();

    DenseLayer &operator=(const DenseLayer &layer);

    DenseLayer(DenseLayer &&);

    DenseLayer &operator=(DenseLayer &&);

   private:
    void setup_activation(const std::string &activation);
};

#endif  // DENSELAYER_HPP