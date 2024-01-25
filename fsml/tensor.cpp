#include "tensor.h"
#include "../fsml/backend/ops.cuh"

#include <vector>

namespace tensor {
  /*
   * given a size, will initialize a tensor with 0
  */
  tensor::tensor(int size): size_(size), data_(size, 0) {}

  /*
  * give a size, and a single value initialize 
  * array with given value
  */
  tensor::tensor(int size, float value): size_(size), data_(size, value) {}

  
  tensor tensor::operator+(const tensor& other) const { 
    const float* c = ops::tensor_add(data_.data(), other.data_.data());
  }
}
