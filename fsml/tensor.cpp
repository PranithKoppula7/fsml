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

  std::vector<int> out_shape = broadcast_shape(std::vector<std::vector<int>>{
    shape(),
    other.shape()
  });

  if (shape().size() > out_shape.size()) {
    throw std::runtime_error("Cannot broadcast tensor");
  }

  int size = 1;
  for (int s: out_shape) {
    size *= s;
  }

  tensor a = broadcast(*this, out_shape);
  tensor b = broadcast(other, out_shape);

  tensor res = Add->forward(a, b);

  res.parents_.push_back(this);
  res.parents_.push_back(&other);

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


tensor tensor::broadcast(tensor& a, std::vector<int> shape) {
  int size = 1;
  for (int i = 0; i < shape.size(); i++) {
    size *= shape[i];
  }
  std::vector<float> data;
  float* a_data = a.data();
  int boundary = a.size();
  for (int i = 0; i < size; i++) {
    data.push_back(a_data[i % boundary]);
  }
  return tensor(data, shape);
}

/** assumes a and b strides are adjusted before calling */
std::pair<std::vector<float>, std::vector<float>> tensor::broadcast(
  tensor& a,
  tensor& other) {

  std::pair<std::vector<float>, std::vector<float>> ans;
  int size = other.size();
  std::vector<float> one;
  std::vector<float> two;
  for (int i = 0; i < size; i++) {
    int a_idx = elem_to_loc(i, shape(), a.data_.strides());
    int b_idx = elem_to_loc(i, other.data_.shape(), other.data_.strides());
    one.push_back(a.data_.getFromOffset(a_idx));
    two.push_back(other.data_.getFromOffset(b_idx));
  }
  ans.first = one;
  ans.second = two;
  return ans;
}

size_t elem_to_loc(int elem, std::vector<int> shape, std::vector<size_t> strides) {
   size_t loc = 0;
    for (int i = shape.size() - 1; i >= 0; --i) {
      auto q_and_r = ldiv(elem, shape[i]);
      loc += q_and_r.rem * strides[i];
      elem = q_and_r.quot;
    }
    return loc;
}

tensor tensor::broadcast_to(tensor& x, std::vector<int> shape) {
  if (x.shape() == shape) return x;

  int diff = shape.size() - x.size();
  std::vector<size_t> strides(shape.size(), 0);
  for (int i = x.shape().size() - 1; i >= 0; i--) {
    strides[i + diff] = x.shape()[i] == 1 ? 0 : x.data_.strides()[i];
  }

  return tensor(buffer<float>(shape, x.data_vec, strides));
}

std::vector<std::vector<int>> pad_left(std::vector<std::vector<int>> shapes) {
  int max = 0;
  for (std::vector<int> s: shapes) {
    max = std::max(max, (int)s.size());
  }

  std::vector<std::vector<int>> ans;
  for (std::vector<int> s: shapes) {
    if (s.size() == max) {
      ans.push_back(s);
    } else {
      std::vector<int> s_;
      int numOnes = max - s.size();
      for (int i = 0; i < numOnes; i++) {
        s_.push_back(1);
      }
      for (int i = 0; i < s.size(); i++) {
        s_.push_back(s[i]);
      }
      ans.push_back(s_);
    }
  }

  return ans;
}

std::vector<int> broadcast_shape(std::vector<std::vector<int>> shapes) {
  if (shapes.size() == 0) return std::vector<int>{};

  std::vector<std::vector<int>> padded = pad_left(shapes);

  int size = padded[0].size();
  std::vector<int> ans;
  for (int i = 0; i < size; i++) {
    int currDimMax = 0;
    for (std::vector<int> s: padded) {
      currDimMax = std::max(currDimMax, s[i]);
    }
    ans.push_back(currDimMax);
  }
  return ans;
}
