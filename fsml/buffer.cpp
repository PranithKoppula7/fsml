#include "buffer.h"

#include <stdexcept>

template<typename T>
buffer<T>::buffer(std::vector<int> shape): shape(shape) {
    int total_elems = 1;
    for (int dim: shape) {
        total_elems *= dim;
    }

    if (total_elems == 0) {
        throw std::invalid_argument("Shape cannot contain 0");
    }

    data = std::make_unique<T*>((T*)(total_elems * sizeof(T)));
    strides.resize(shape.size());
    std::size_t stride = sizeof(T);
    for (int i = shape.size() - 1; i >= 0; --i) {
        strides[i] = stride;
        stride *= shape[i];
    }
}

template<typename T>
std::vector<int> buffer<T>::getShape() {
    return shape;
}

template<typename T>
std::vector<std::size_t> buffer<T>::getStrides() {
    return strides;
}