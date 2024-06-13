#include "KNearestNeighbours.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "LinearAlgebra.hpp"
#include "Utilities.hpp"

KNearestNeighbours::KNearestNeighbours(std::vector<std::vector<double>> input, std::vector<double> output, int k)
    : input(input), output(output), k(k) {
}

std::vector<double> KNearestNeighbours::getKNearestNeighbours(std::vector<double> x) {
    std::vector<double> knn;
    std::vector<std::vector<double>> inputCopy = input;
    for (int i = 0; i < k; i++) {
        int neighbour = 0;
        double curr = 0, distance = std::numeric_limits<double>::max();
        for (int j = 0; j < inputCopy.size(); j++) {
            curr = LinearAlgebra::euclideanDistance<double>(x, inputCopy[j]);
            bool nearer = curr < distance;
            if (nearer) {
                neighbour = j;
                distance = curr;
            }
        }
        knn.push_back(neighbour);
        inputCopy.erase(input.begin() + neighbour);
    }
    return knn;
}

int KNearestNeighbours::getClass(std::vector<double> x) {
    std::map<int, int> classes;
    for (int i = 0; i < x.size(); i++) {
        classes[output.size()] = 0;
    }
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < output.size(); j++) {
            if (x[i] == output[j]) classes[x[i]]++;
        }
    }
    int max = classes[output[0]], res = output[0];
    for (auto [i, j] : classes) {
        if (j >= max) {
            max = j;
            res = i;
        }
    }
    return res;
}

int KNearestNeighbours::modelTest(std::vector<double> x) {
    return KNearestNeighbours::getClass(KNearestNeighbours::getKNearestNeighbours(x));
}

std::vector<double> KNearestNeighbours::modelVectorTest(std::vector<std::vector<double>> x) {
    std::vector<double> y;
    for (int i = 0; i < x.size(); i++) {
        y.push_back(KNearestNeighbours::modelTest(x[i]));
    }
    return y;
}
double KNearestNeighbours::score() {
    return Utilities::performance(KNearestNeighbours::modelVectorTest(input), output);
}