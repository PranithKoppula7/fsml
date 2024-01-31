#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <vector>

namespace tensor {

class tensor {

public:

  // empty initalization (randomly initialized)
  tensor(int size);

  // with a single value
  tensor(int size, float value);  

  tensor operator+(const tensor& other) const;

private:
  int size_;
  float* data_;
};

} // namespace tensor
#endif
