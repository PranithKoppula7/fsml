#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

namespace tensor {

class tensor {

public:
  float* data_;

  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  ~tensor();

  tensor operator+(const tensor& other) const;

private:
  int size_;
};

} // namespace tensor
#endif
