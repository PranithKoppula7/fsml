#include "tensor.h"
#include "../fsml/backend/tensor.cuh"
#include "operation.h"

#include <cstddef>
#include <iostream>

/*
  * given a size, will initialize a tensor with 0
*/
tensor::tensor(int size): size_(size) {
  size_t nBytes = size * sizeof(float);
  data_ = (float*)malloc(nBytes);
  for (int i = 0; i < size; i++) {
    data_[i] = 0;
  }
  shape_.push_back(size);
}

/*
* give a size, and a single value initialize 
* array with given value
*/
tensor::tensor(int size, float value): size_(size) {
  size_t nBytes = size * sizeof(float);
  data_ = (float*)malloc(nBytes);
  for (int i = 0; i < size; i++) {
    data_[i] = value;
  }
  shape_.push_back(size);
}

tensor::tensor(int size, float* data): size_(size), data_(data) {
  shape_.push_back(size);
}

tensor::tensor(int size, float* data, std::vector<int> shape):
  size_(size), data_(data), shape_(shape) {}

/*
* returns a copy of data 
*/
float* tensor::data() {
  size_t nBytes = size_ * sizeof(float);
  float* copy = (float*)malloc(nBytes);
  for(int i = 0; i < size_; i++) {
    copy[i] = data_[i];
  }
  return copy;
}

int tensor::size() {
  return size_;
}

std::vector<int> tensor::shape() {
  return shape_;
}

std::string tensor::repr() {
  std::string s = "";
  s += "<Tensor size: " + std::to_string(size_);
  s += ", data: [";
  for (int i = 0; i < size_; i++) {
    s += std::to_string(data_[i]);
    if (i < size_ - 1) {
      s += ", ";
    }
  }
  s += "]>";
  return s;
}

tensor tensor::operator+(const tensor& other) const {
  return add::forward(*this, other);
}
