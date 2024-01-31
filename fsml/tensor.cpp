#include "tensor.h"
#include "../fsml/backend/ops.cuh"

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


  tensor tensor::operator+(const tensor& other) const { 
    float* a = data_;
    float* b = other.data_;
    float* c = Ops::tensor_add(a, b);
    std::cout << "c = " << c << std::endl;
    return NULL;
  }
}
