// KNearestNeighbours_hpp

#ifndef KNEARESTNEIGHBOURS_HPP
#define KNEARESTNEIGHBOURS_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include "LinearAlgebra.hpp"
#include "Utilities.hpp"

class KNearestNeighbours {
   public:
    int k;
    std::vector<std::vector<double>> input;
    std::vector<double> output;

    KNearestNeighbours(std::vector<std::vector<double>> input, std::vector<double> output, int k);

    std::vector<double> getKNearestNeighbours(std::vector<double> x);

    int getClass(std::vector<double> x);

    int modelTest(std::vector<double> x);

    std::vector<double> modelVectorTest(std::vector<std::vector<double>> x);

    double score();
};

#endif  // KNEARESTNEIGHBOURS_HPP