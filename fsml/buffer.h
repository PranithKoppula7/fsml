#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>

template <typename T>
class buffer {

public:
    buffer(std::vector<int> shape);

    std::vector<int> getShape();
    std::vector<std::size_t> getStrides();

private:
    std::vector<int> shape;
    std::vector<std::size_t> strides;
    std::unique_ptr<T*> data;
};