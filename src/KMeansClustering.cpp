#include "KMeansClustering.hpp"

#include <cmath>
#include <cstdlib>
#include <limits>

std::vector<int> KMeansClustering::fit(const std::vector<std::vector<double>>& data, int k) {
    size_t n = data.size();
    size_t d = data[0].size();
    std::vector<std::vector<double>> centroids(k, std::vector<double>(d));
    std::vector<int> labels(n);

    for (int i = 0; i < k; ++i) {
        centroids[i] = data[std::rand() % n];
    }

    bool changed = true;
    while (changed) {
        changed = false;

        for (size_t i = 0; i < n; ++i) {
            double min_dist = std::numeric_limits<double>::max();
            int best_cluster = -1;
            for (int j = 0; j < k; ++j) {
                double dist = 0.0;
                for (size_t dim = 0; dim < d; ++dim) {
                    dist += std::pow(data[i][dim] - centroids[j][dim], 2);
                }
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = j;
                }
            }
            if (labels[i] != best_cluster) {
                labels[i] = best_cluster;
                changed = true;
            }
        }

        for (int j = 0; j < k; ++j) {
            std::vector<double> sum(d, 0.0);
            int count = 0;
            for (size_t i = 0; i < n; ++i) {
                if (labels[i] == j) {
                    for (size_t dim = 0; dim < d; ++dim) {
                        sum[dim] += data[i][dim];
                    }
                    count++;
                }
            }
            for (size_t dim = 0; dim < d; ++dim) {
                centroids[j][dim] = sum[dim] / count;
            }
        }
    }
    return labels;
}
