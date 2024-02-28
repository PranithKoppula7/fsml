#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>

namespace tensor {

class tensor {

public:
  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  // ~tensor();

  float* getData();

  int getSize();

  tensor operator+(const tensor& other) const;

  // std::string repr();
  std::string repr();

private:
  int size_;
  float* data_;
};

} // namespace tensor
#endif
