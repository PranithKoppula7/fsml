#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>

template <typename T>
class buffer {

public:
    buffer(std::vector<int> shape, std::vector<T> data);
    buffer(std::vector<int> shape, std::vector<T> data, std::vector<std::size_t> strides);

    buffer() = default;

    std::vector<int> shape();
    std::vector<std::size_t> strides();
    int size();
    T* data();
    

    T& get(std::vector<int> index);
    void set(std::vector<int> index, T value);

    buffer<T> reshape(std::vector<int> newShape);

private:
    std::vector<int> shape_;
    std::vector<std::size_t> strides_;
    T* data_;
    int size_;
    // std::vector<T> data;


    int get1DIndex(std::vector<int> index);
};