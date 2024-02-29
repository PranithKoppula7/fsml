#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>
#include <vector>

namespace tensor {

class tensor {

public:
  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  tensor(int size, float* data, std::vector<int> shape_);

  // ~tensor();

  /* getters */
  float* data();

  int size();

  tensor operator+(const tensor& other) const;

  std::string repr();

private:
  int size_;
  float* data_;
  std::vector<int> shape_;
};

} // namespace tensor
#endif
