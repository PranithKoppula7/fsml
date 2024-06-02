#include "buffer.h"

#include <stdexcept>
#include <iostream>

template<typename T>
buffer<T>::buffer(std::vector<int> shape,
                  std::vector<T> data): shape_(shape) {
    int total_elems = 1;
    for (int dim: shape) {
        total_elems *= dim;
    }

    if (total_elems == 0) {
        throw std::invalid_argument("Shape cannot contain 0");
    }

    if (total_elems != data.size()) {
        throw std::invalid_argument("data_ is not same size as shape");
    }

    size_ = total_elems;

    size_t nBytes = size_ * sizeof(T);
    data_ = (T*)malloc(nBytes);
    for (int i = 0; i < size_; i++) {
        data_[i] = data[i];
    }

    strides_.resize(shape.size());
    std::size_t stride = sizeof(T);
    for (int i = shape.size() - 1; i >= 0; --i) {
        strides_[i] = stride;
        stride *= shape[i];
    }
}

template<typename T>
std::vector<int> buffer<T>::shape() {
    return shape_;
}

template<typename T>
std::vector<std::size_t> buffer<T>::strides() {
    return strides_;
}

template<typename T>
int buffer<T>::size() {
    return size_;
}

template<typename T>
T* buffer<T>::data() {
    return data_;
}

template<typename T>
buffer<T> buffer<T>::reshape(std::vector<int> newShape) {
    // arg check
    for (int dim: shape_) {
        if (dim == 0) {
            throw std::invalid_argument("newShape cannot contain 0");
        }
        if (dim < 0) {
            throw std::invalid_argument("newShape cannot contain negative numbers");
        } 
    }
}

template<typename T>
void buffer<T>::set(std::vector<int> index, T value) {
    if (index.size() != shape_.size()) {
        throw std::invalid_argument("index size must be same as shape size");
    }

    for (int i = 0; i < shape_.size(); i++) {
        if (index[i] > shape_[i] || index[i] < 0) {
            throw std::invalid_argument("index contains invalid dimension");
        }
    }
    char* offset = (char*)data_;
    for (int i = 0; i < strides_.size(); i++) {
        offset += index[i] * strides_[i];
    }
    T* ptr = (T*)offset;
    *ptr = value;
}

template<typename T>
T& buffer<T>::get(std::vector<int> index) {
    if (index.size() != shape_.size()) {
        throw std::invalid_argument("index size must be same as shape size");
    }

    for (int i = 0; i < shape_.size(); i++) {
        if (index[i] > shape_[i] || index[i] < 0) {
            throw std::invalid_argument("index contains invalid dimension");
        }
    }
    // stride
    // can do data_[get1DIndex(index)] but more time compelxity
    // cast to char because char* is smallest addressable unit
    // so adding moves char* by that many bytes
    // atleast that's what gemini says
    // its weird, deal with it
    char* offset = (char*)data_;
    for (int i = 0; i < strides_.size(); i++) {
        offset += index[i] * strides_[i];
    }
    return *((T*)offset);
}

template<typename T>
int buffer<T>::get1DIndex(std::vector<int> index) {
    if (index.size() != shape_.size()) {
        throw std::invalid_argument("index size must be same as shape size");
    }

    for (int i = 0; i < shape_.size(); i++) {
        if (index[i] > shape_[i] || index[i] < 0) {
            throw std::invalid_argument("index contains invalid dimension");
        }
    }

    // o(n**2) 
    int index_ = 0;
    for (int i = 0; i < index.size() - 1; i++) {
        int curr = index[i];
        int j = 1;
        while (j < shape_.size()) {
            curr *= shape_[j];
            j++;
        }
        index_ += curr;
    }
    index_ += index[index.size() - 1];
    return index_;

}