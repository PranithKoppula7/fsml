#include "tensor.h"
#include "../fsml/backend/tensor.cuh"

#include <cstddef>
#include <iostream>

namespace tensor {
  /*
   * given a size, will initialize a tensor with 0
  */
  tensor::tensor(int size): size_(size) {
    // malloc host memory
    size_t nBytes = size * sizeof(float);

    data_ = (float*)malloc(nBytes);
    for (int i = 0; i < size; i++) {
      data_[i] = 0;
    }
  }

  /*
  * give a size, and a single value initialize 
  * array with given value
  */
  tensor::tensor(int size, float value): size_(size) {
    // malloc host memory
    size_t nBytes = size * sizeof(float);

    data_ = (float*)malloc(nBytes);
    for (int i = 0; i < size; i++) {
      data_[i] = value;
    }
  }


  tensor::tensor(float* data): data_(data) {}

  tensor tensor::operator+(const tensor& other) const { 
    float* a = data_;
    float* b = other.data_;
    float* c = Tensor::tensor_add(a, b);
    std::cout << "c = " << c[0] << std::endl;
    return tensor(c);
  }
}
