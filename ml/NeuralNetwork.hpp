// NeuralNetwork_hpp

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "ActivationFunctions.hpp"
#include "DenseLayer.hpp"
#include "LinearAlgebra.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::vector<T>> const &A) {
    out.precision(4);
    for (const auto &a : A) {
        for (const auto &x : a) {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    }
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::pair<T, T> &A) {
    out.precision(4);
    std::cout << "(" << A.first << ", " << A.second << ")";
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &A) {
    out.precision(4);
    for (const auto &a : A) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;
    return out;
}

template <typename T>
std::vector<T> insert(const std::vector<T> &A, const T &x) {
    std::vector<T> B;
    B.resize(A.size() + 1);
    for (size_t i = 0; i < A.size(); i++) {
        B[i] = A[i];
    }
    B[B.size() - 1] = x;
    return B;
}

template <typename T>
T square(const T &x) { return x * x; }

template <typename T>
std::vector<T> pop_front(const std::vector<T> &A) {
    std::vector<T> B;
    B.resize(A.size() - 1);
    for (int i = 1; i < A.size(); i++) {
        B[i - 1] = A[i];
    }
    return B;
}

template <typename T>
std::vector<T> pop_back(const std::vector<T> &A) {
    std::vector<T> B(A.size());
    B.resize(A.size() - 1);
    for (int i = 0; i < A.size() - 1; i++) {
        B[i] = A[i];
    }
    return B;
}

template <typename T>
void vector_shuffle(std::vector<std::vector<std::vector<T>>> &A,
                    std::vector<std::vector<std::vector<T>>> &B) {
    if (A.size() != B.size()) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr
            << "Cannot shuffle vectors with different sizes: ";
        std::cerr << A.size() << " and " << B.size() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < A.size(); i++) {
        std::srand(std::chrono::system_clock::now().time_since_epoch().count());
        size_t random_index = std::rand() % A.size();
        std::swap(A[i], A[random_index]);
        std::swap(B[i], B[random_index]);
    }
    return;
}

template <typename T>
void random_matrix(std::vector<std::vector<T>> &A, const std::pair<size_t, size_t> &shape, const T &low, const T &high) {
    A.clear();
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<T> distribution(low, high);
    for (size_t i = 0; i < shape.first; i++) {
        std::vector<T> row;
        row.resize(shape.second);
        for (auto &r : row) {
            r = distribution(generator);
        }
        A.push_back(row);
    }
    return;
}

template <typename T>
void unit_matrix(std::vector<std::vector<T>> &A, const std::pair<size_t, size_t> &shape) {
    A.clear();
    for (size_t i = 0; i < shape.first; i++) {
        std::vector<T> row;
        row.resize(shape.second);
        row[i] = T(1);
        A.push_back(row);
    }
    return;
}

template <typename T>
void zero_matrix(std::vector<std::vector<T>> &A, const std::pair<size_t, size_t> &shape) {
    A.clear();
    for (size_t i = 0; i < shape.first; i++) {
        std::vector<T> row;
        row.resize(shape.second);
        A.push_back(row);
    }
    return;
}

template <typename T>
T sum(const std::vector<std::vector<T>> &A) {
    T total = 0;
    for (const auto &a : A) {
        total = accumulate(a.begin(), a.end(), 0);
    }
    return total;
}

template <typename T>
std::pair<int, int> get_shape(const std::vector<std::vector<T>> &A) {
    const size_t sub_size = (*A.begin()).size();
    for (const auto &a : A) {
        if (a.size() != sub_size) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Vector is not a 2D matrix" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    return std::make_pair(A.size(), A[0].size());
}

template <typename T>
std::vector<std::vector<T>> apply_function(const std::vector<std::vector<T>> &A, T (*fn)(const T &x)) {
    std::vector<std::vector<double>> B = A;
    for (int i = 0; i < B.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            B[i][j] = fn(A[i][j]);
        }
    }
    return B;
}

template <typename T>
std::vector<std::vector<T>> apply_activation_function(const std::vector<std::vector<T>> &A, const bool &b, T (*fn)(const T &x, const bool &)) {
    std::vector<std::vector<double>> B = A;
    for (int i = 0; i < B.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            B[i][j] = fn(A[i][j], b);
        }
    }
    return B;
}

template <typename T>
std::vector<std::vector<T>> operator+(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);
    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Supplied vectors have different shapes ";
        std::cerr << shape_a << " and " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::vector<T>> C(A.size(), std::vector<T>(A[0].size()));
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

template <typename T>
std::vector<std::vector<T>> operator-(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B) {
    const auto shape_a = get_shape(A);
    const auto shape_b = get_shape(B);

    if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
        std::cerr << "ERROR (" << __func__ << ") : ";
        std::cerr << "Supplied vectors have different shapes ";
        std::cerr << shape_a << " and " << shape_b << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::vector<T>> C(A.size(), std::vector<T>(A[0].size()));
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

template <typename T>
std::vector<std::vector<T>> operator*(const std::vector<std::vector<T>> &A, const T &val) {
    std::vector<std::vector<double>> B = A;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            B[i][j] = A[i][j] * val;
        }
    }
    return B;
}

template <typename T>
std::vector<std::vector<T>> operator/(const std::vector<std::vector<T>> &A, const T &val) {
    std::vector<std::vector<double>> B = A;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            B[i][j] = A[i][j] / val;
        }
    }
    return B;
}

class Layer {
   public:
    double (*activation_function)(const double &, const bool &);
    int neurons;
    std::string activation;
    std::vector<std::vector<double>> kernel;

    Layer(const int &neurons, const std::string &activation, const std::pair<size_t, size_t> &kernel_shape, const bool &random_kernel) {
        setup_activation(activation);
        this->neurons = neurons;
        if (random_kernel) {
            random_matrix(kernel, kernel_shape, -1.0, 1.0);
        } else {
            unit_matrix(kernel, kernel_shape);
        }
    }

    Layer(const int &neurons, const std::string &activation, const std::vector<std::vector<double>> &kernel) {
        setup_activation(activation);
        this->neurons = neurons;
        this->kernel = kernel;
    }

    Layer(const Layer &layer) = default;

    ~Layer() = default;

    Layer &operator=(const Layer &layer) = default;

    Layer(Layer &&) = default;

    Layer &operator=(Layer &&) = default;

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

class NeuralNetwork {
   private:
    std::vector<Layer> layers;

    NeuralNetwork(
        const std::vector<std::pair<int, std::string>> &config,
        const std::vector<std::vector<std::vector<double>>> &kernels) {
        if (config.begin()->second != "none") {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr
                << "First layer can't have activation other than none, got "
                << config.begin()->second;
            std::cerr << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (config.size() <= 1) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid size of network, ";
            std::cerr << "At least two layers are required";
            std::exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < config.size(); i++) {
            layers.emplace_back(Layer(
                config[i].first, config[i].second, kernels[i]));
        }
        std::cout << "INFO: Network constructed." << std::endl;
    }

    std::vector<std::vector<std::vector<double>>> __detailed_single_prediction(const std::vector<std::vector<double>> &X) {
        std::vector<std::vector<std::vector<double>>> details;
        std::vector<std::vector<double>> current_pass = X;
        details.emplace_back(X);
        for (const auto &l : layers) {
            std::pair<int, int> x_size = get_shape(current_pass);
            std::pair<int, int> y_size = get_shape(l.kernel);
            current_pass = LinearAlgebra::matrixMultiply(current_pass, l.kernel);
            current_pass = apply_activation_function(current_pass, 0, l.activation_function);
            details.emplace_back(current_pass);
        }
        return details;
    }

   public:
    NeuralNetwork() = default;

    explicit NeuralNetwork(
        const std::vector<std::pair<int, std::string>> &config) {
        if (config.begin()->second != "none") {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr
                << "First layer can't have activation other than none, got "
                << config.begin()->second;
            std::cerr << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (config.size() <= 1) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid size of network, ";
            std::cerr << "At least two layers are required";
            std::exit(EXIT_FAILURE);
        }

        layers.push_back(Layer(
            config[0].first, config[0].second,
            {config[0].first, config[0].first}, false));

        for (size_t i = 1; i < config.size(); i++) {
            layers.push_back(Layer(
                config[i].first, config[i].second,
                {config[i - 1].first, config[i].first}, true));
        }
        std::cout << "INFO: Network constructed." << std::endl;
    }

    NeuralNetwork(const NeuralNetwork &model) = default;

    ~NeuralNetwork() = default;

    NeuralNetwork &operator=(const NeuralNetwork &model) = default;

    NeuralNetwork(NeuralNetwork &&) = default;

    NeuralNetwork &operator=(NeuralNetwork &&) = default;

    std::pair<std::vector<std::vector<std::vector<double>>>,
              std::vector<std::vector<std::vector<double>>>>
    get_XY_from_csv(const std::string &file_name, const bool &last_label,
                    const bool &normalize, const int &slip_lines = 1) {
        std::ifstream in_file;
        in_file.open(file_name.c_str(), std::ios::in);
        if (!in_file.is_open()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Unable to open file: " << file_name << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::vector<std::vector<std::vector<double>>> X, Y;
        std::string line;
        for (int i = 0; i < slip_lines; i++) {
            std::getline(in_file, line, '\n');
        }
        while (!in_file.eof() && std::getline(in_file, line, '\n')) {
            std::vector<double> x_data, y_data;
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ',')) {
                x_data = insert(x_data, std::stod(token));
            }
            if (last_label) {
                y_data.resize(this->layers.back().neurons);
                // Classification
                if (y_data.size() > 1) {
                    y_data[x_data[x_data.size() - 1]] = 1;
                }
                // Regression
                else {
                    y_data[0] = x_data[x_data.size() - 1];
                }
                x_data = pop_back(x_data);
            } else {
                y_data.resize(this->layers.back().neurons);
                // Classification
                if (y_data.size() > 1) {
                    y_data[x_data[x_data.size() - 1]] = 1;
                }
                // Regression
                else {
                    y_data[0] = x_data[x_data.size() - 1];
                }
                x_data = pop_front(x_data);
            }
            X.push_back({x_data});
            Y.push_back({y_data});
        }
        if (normalize) {
            X = LinearAlgebra::minmax(X, 0.01, 1.0);
        }
        in_file.close();
        return make_pair(X, Y);
    }

    std::vector<std::vector<double>> single_predict(
        const std::vector<std::vector<double>> &X) {
        auto activations = this->__detailed_single_prediction(X);
        return activations.back();
    }

    std::vector<std::vector<std::vector<double>>> batch_predict(
        const std::vector<std::vector<std::vector<double>>> &X) {
        std::vector<std::vector<std::vector<double>>> predicted_batch(
            X.size());
        for (size_t i = 0; i < X.size(); i++) {
            predicted_batch[i] = this->single_predict(X[i]);
        }
        return predicted_batch;
    }

    void fit(const std::vector<std::vector<std::vector<double>>> &X_,
             const std::vector<std::vector<std::vector<double>>> &Y_,
             const int &epochs = 100, const double &learning_rate = 0.01,
             const size_t &batch_size = 32, const bool &shuffle = true) {
        std::vector<std::vector<std::vector<double>>> X = X_, Y = Y_;
        if (X.size() != Y.size()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "X and Y have different sizes" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::cout << "INFO: Training started." << std::endl;
        for (int epoch = 1; epoch <= epochs; epoch++) {
            if (shuffle) {
                vector_shuffle(X, Y);
            }
            auto start = std::chrono::high_resolution_clock::now();
            double loss = 0, acc = 0;
            for (int batch_start = 0; batch_start < X.size(); batch_start += batch_size) {
                for (int i = batch_start; i < std::min(X.size(), batch_start + batch_size); i++) {
                    std::vector<std::vector<double>> grad, cur_error, predicted;
                    auto activations = this->__detailed_single_prediction(X[i]);
                    std::vector<std::vector<std::vector<double>>> gradients;
                    gradients.resize(this->layers.size());
                    for (int i = 0; i < gradients.size(); i++) {
                        for (int i = 0; i < gradients.size(); i++) {
                            zero_matrix(
                                gradients[i], get_shape(this->layers[i].kernel));
                        }
                    }
                    predicted = activations.back();
                    cur_error = predicted - Y[i];
                    loss += sum(apply_function(cur_error, square));
                    if (LinearAlgebra::argmax(predicted) == LinearAlgebra::argmax(Y[i])) {
                        acc += 1;
                    }
                    for (int j = this->layers.size() - 1; j >= 1; j--) {
                        cur_error = LinearAlgebra::hadamardProduct(
                            cur_error,
                            apply_activation_function(
                                activations[j + 1],
                                1,
                                this->layers[j].activation_function));
                        grad = LinearAlgebra::matrixMultiply(LinearAlgebra::transpose(activations[j]), cur_error);
                        cur_error = LinearAlgebra::matrixMultiply(cur_error, LinearAlgebra::transpose(this->layers[j].kernel));
                        gradients[j] = gradients[j] + grad / double(batch_size);
                    }
                    for (size_t j = this->layers.size() - 1; j >= 1; j--) {
                        this->layers[j].kernel = this->layers[j].kernel - gradients[j] * learning_rate;
                    }
                }
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            loss /= X.size();
            acc /= X.size();
            std::cout.precision(4);
            std::cout << "Training: Epoch " << epoch << '/' << epochs;
            std::cout << ", Loss: " << loss;
            std::cout << ", Accuracy: " << acc;
            std::cout << ", Time: " << duration.count() / 1e6 << " seconds";
            std::cout << std::endl;
        }
        return;
    }

    void fit_from_csv(const std::string &file_name, const bool &last_label,
                      const int &epochs, const double &learning_rate,
                      const bool &normalize, const int &slip_lines = 1,
                      const size_t &batch_size = 32,
                      const bool &shuffle = true) {
        auto data = this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);
        std::cout << "INFO: Parsing " << file_name << " complete." << std::endl;
        this->fit(data.first, data.second, epochs, learning_rate, batch_size, shuffle);
        std::cout << "INFO: Model fit complete." << std::endl;
        return;
    }

    void evaluate(const std::vector<std::vector<std::vector<double>>> &X,
                  const std::vector<std::vector<std::vector<double>>> &Y) {
        std::cout << "INFO: Evaluation started." << std::endl;
        double acc = 0, loss = 0;
        for (size_t i = 0; i < X.size(); i++) {
            std::vector<std::vector<double>> pred = this->single_predict(X[i]);
            if (LinearAlgebra::argmax(pred) == LinearAlgebra::argmax(Y[i])) {
                acc += 1;
            }
            loss += sum(apply_function((Y[i] - pred), square) * 0.5);
        }
        acc /= X.size();
        loss /= X.size();
        std::cout << "Evaluation: Loss: " << loss;
        std::cout << ", Accuracy: " << acc << std::endl;
        return;
    }

    void evaluate_from_csv(const std::string &file_name, const bool &last_label,
                           const bool &normalize, const int &slip_lines = 1) {
        auto data = this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);
        this->evaluate(data.first, data.second);
        return;
    }

    void save_model(const std::string &_file_name) {
        std::string file_name = _file_name;
        if (file_name.find(".model") == file_name.npos) {
            file_name += ".model";
        }
        std::ofstream out_file;
        out_file.open(file_name.c_str(), std::ofstream::out | std::ofstream::trunc);
        if (!out_file.is_open()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Unable to open file: " << file_name << std::endl;
            std::exit(EXIT_FAILURE);
        }
        /*
            Save Format:

            total_layers
            neurons(1st Layer) activation_name(1st Layer) kernel_shape(1st Layer) kernel_values
            .
            .
            .
            neurons(Nth Layer) activation_name(Nth Layer) kernel_shape(Nth Layer) kernel_value

            Example: Pretrained model with 3 layers
            <pre>
            3
            4 none
            4 4
            1 0 0 0
            0 1 0 0
            0 0 1 0
            0 0 0 1
            6 relu
            4 6
            -1.88963 -3.61165 1.30757 -0.443906 -2.41039 -2.69653
            -0.684753 0.0891452 0.795294 -2.39619 2.73377 0.318202
            -2.91451 -4.43249 -0.804187 2.51995 -6.97524 -1.07049
            -0.571531 -1.81689 -1.24485 1.92264 -2.81322 1.01741
            3 sigmoid
            6 3
            0.390267 -0.391703 -0.0989607
            0.499234 -0.564539 -0.28097
            0.553386 -0.153974 -1.92493
            -2.01336 -0.0219682 1.44145
            1.72853 -0.465264 -0.705373
            -0.908409 -0.740547 0.376416
            </pre>
        */

        out_file << layers.size();
        out_file << std::endl;
        for (const auto &layer : this->layers) {
            out_file << layer.neurons << ' ' << layer.activation << std::endl;
            const auto shape = get_shape(layer.kernel);
            out_file << shape.first << ' ' << shape.second << std::endl;
            for (const auto &row : layer.kernel) {
                for (const auto &val : row) {
                    out_file << val << ' ';
                }
                out_file << std::endl;
            }
        }
        std::cout << "INFO: Model successfully saved to ";
        std::cout << file_name << "." << std::endl;
        out_file.close();
        return;
    }

    NeuralNetwork load_model(const std::string &file_name) {
        std::ifstream in_file;
        in_file.open(file_name.c_str());
        if (!in_file.is_open()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Unable to open file: " << file_name << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::vector<std::pair<int, std::string>> config;
        std::vector<std::vector<std::vector<double>>> kernels;
        size_t total_layers = 0;
        in_file >> total_layers;
        for (size_t i = 0; i < total_layers; i++) {
            int neurons = 0;
            std::string activation;
            size_t shape_a = 0, shape_b = 0;
            std::vector<std::vector<double>> kernel;
            in_file >> neurons >> activation >> shape_a >> shape_b;
            for (size_t r = 0; r < shape_a; r++) {
                std::vector<double> row(shape_b);
                for (size_t c = 0; c < shape_b; c++) {
                    in_file >> row[c];
                }
                kernel.push_back(row);
            }
            config.emplace_back(make_pair(neurons, activation));
            kernels.emplace_back(kernel);
        }
        std::cout << "INFO: Model successfully loaded." << std::endl;
        in_file.close();
        return NeuralNetwork(
            config, kernels);
    }

    void summary() {
        std::cout
            << "================================================================="
            << std::endl;
        std::cout << "\t\t\t+ MODEL SUMMARY +\t\t\t\n";
        std::cout
            << "================================================================="
            << std::endl;
        for (size_t i = 1; i <= layers.size(); i++) {
            std::cout << i << ")";
            std::cout << " Neurons: "
                      << layers[i - 1].neurons;
            std::cout << ", Activation: "
                      << layers[i - 1].activation;
            std::cout << ", Kernel: "
                      << get_shape(layers[i - 1].kernel);
            std::cout << std::endl;
        }
        std::cout
            << "================================================================="
            << std::endl;
        return;
    }
};

#endif  // NeuralNetwork_hpp