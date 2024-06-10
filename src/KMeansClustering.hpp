#ifndef KMEANSCLUSTERING_HPP
#define KMEANSCLUSTERING_HPP

#include <vector>

class KMeansClustering {
   public:
    static std::vector<int> fit(const std::vector<std::vector<double>>& data, int k);
};

#endif  // KMEANSCLUSTERING_HPP
