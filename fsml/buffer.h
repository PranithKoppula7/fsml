#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>

template <typename T>
class buffer {

public:
    buffer(std::vector<int> shape, std::vector<T> data_);

    std::vector<int> getShape();
    std::vector<std::size_t> getStrides();
    std::vector<T> getData();
    

    T& operator[](std::vector<int> index);

    buffer<T> reshape(std::vector<int> newShape);

private:
    std::vector<int> shape;
    std::vector<std::size_t> strides;
    std::vector<T> data;

    int get1DIndex(std::vector<int> index);
};