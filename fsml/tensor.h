#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

namespace tensor {

class tensor {

public:
  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  // ~tensor();

  float* getData();

  tensor operator+(const tensor& other) const;

private:
  int size_;
  float* data_;
};

} // namespace tensor
#endif
