#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <vector>

namespace tensor {

class tensor {

public:
  float* data_;

  // zero init
  tensor(int size);

  // with a single value
  tensor(int size, float value);  

  // with list/array
  tensor(float* data);

  tensor operator+(const tensor& other) const;

private:
  int size_;
};

} // namespace tensor
#endif
