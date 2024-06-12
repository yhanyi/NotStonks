// Transforms.hpp

#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

#include <string>
#include <vector>

#include "LinearAlgebra.hpp"

class Transforms {
   public:
    template <typename T>
    static std::vector<std::vector<T>> discreteCosineTransform(std::vector<std::vector<T>> x);
};

#endif  // TRANSFORMS_HPP