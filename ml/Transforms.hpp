// Transforms.hpp

#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

#include <string>
#include <vector>

#include "LinearAlgebra.hpp"

namespace MLCPP {
class Transforms {
   public:
    template <typename T>
    static std::vector<std::vector<T>> discreteCosineTransform(std::vector<std::vector<T>> x);
};
}  // namespace MLCPP

#endif  // TRANSFORMS_HPP