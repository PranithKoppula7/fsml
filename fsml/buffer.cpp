#include "buffer.h"

#include <stdexcept>

template<typename T>
buffer<T>::buffer(std::vector<int> shape,
                  std::vector<T> data_): shape(shape) {
    int total_elems = 1;
    for (int dim: shape) {
        total_elems *= dim;
    }

    if (total_elems == 0) {
        throw std::invalid_argument("Shape cannot contain 0");
    }

    if (total_elems != data_.size()) {
        throw std::invalid_argument("data_ is not same size as shape");
    }

    data = data_;

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

template<typename T>
std::vector<T> buffer<T>::getData() {
    return data;
}

template<typename T>
buffer<T> buffer<T>::reshape(std::vector<int> newShape) {
    // arg check
    for (int dim: shape) {
        if (dim == 0) {
            throw std::invalid_argument("newShape cannot contain 0");
        }
        if (dim < 0) {
            throw std::invalid_argument("newShape cannot contain negative numbers");
        } 
    }
}

template<typename T>
T& buffer<T>::operator[](std::vector<int> index) {
    return data[get1DIndex(index)];
}

template<typename T>
int buffer<T>::get1DIndex(std::vector<int> index) {
    if (index.size() != shape.size()) {
        throw std::invalid_argument("index size must be same as shape size");
    }

    int index_ = 0;
    for (int i = 0; i < index.size() - 1; i++) {
        int curr = index[i];
        int j = 1;
        while (j < shape.size()) {
            curr *= shape[j];
            j++;
        }
        index_ += curr;
    }
    index_ += index[index.size() - 1];
    return index_;
}