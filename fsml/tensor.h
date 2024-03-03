#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>
#include <vector>

class tensor {

public:
  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  tensor(int size, float* data, std::vector<int> shape);

  float* data();

  int size();

  std::vector<int> shape();

  tensor operator+(const tensor& other) const;

  std::string repr();

private:
  int size_;
  float* data_;
  std::vector<int> shape_;
};

#endif
