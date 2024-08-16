#include "tensor.h"
#include "../fsml/backend/tensor.cuh"
#include "operation.h"
#include "graph.h"

#include <cstddef>
#include <stdlib.h>
#include <iostream>

tensor::tensor(std::vector<float> data, std::vector<int> shape) {
  data_ = buffer<float>(shape, data);
  data_vec = data;
}

/*
* returns a copy of data 
*/
float* tensor::data() {
  return data_.data();
}

int tensor::size() {
  return data_.size();
}

std::vector<int> tensor::shape() {
  return data_.shape();
}

tensor tensor::operator+(tensor& other) {
  add* Add = new add();
  tensor res = Add->forward(*this, other);
  res.parents_.push_back(this);
  res.parents_.push_back(&other);
  return res;

}

tensor tensor::operator+(float other) {
  add* Add = new add();
  tensor other_ = tensor(std::vector<float>{other}, std::vector<int>{1});
  tensor res = Add->forward(*this, other_);
  res.parents_.push_back(this);
  res.parents_.push_back(&other_);
  return res;
}

void tensor::backward() {
  grad = new tensor(std::vector<float>(size(), 1.0), std::vector<int>{size()});
  ctx_->backward(*this);
}

void tensor::create_graph() {
  graph::run(*this);
}

std::string tensor::repr() {
  std::string s = "";
  int size_ = size();
  float* data_ = data();
  s += "<Tensor size: " + std::to_string(size_);
  s += ", data: [";
  for (int i = 0; i < size_; i++) {
    s += std::to_string(data_[i]);
    if (i < size_ - 1) {
      s += ", ";
    }
  }
  s += "]>\n";
  return s;
}
