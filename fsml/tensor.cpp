#include "tensor.h"
#include "../fsml/backend/tensor.cuh"
#include "operation.h"
#include "graph.h"

#include <cstddef>
#include <stdlib.h>
#include <iostream>

tensor::tensor(std::vector<float> data, std::vector<int> shape) {
  data_ = buffer<float>(shape, data);
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

  if (shape() == other.shape()) {
    tensor t = Add->forward(*this, other);
    t.parents_.push_back(this);
    t.parents_.push_back(&other);
    return t;
  }



  // tensor t = Add->forward(*this, other);
  std::vector<int> out_shape = broadcast_shape(std::vector<std::vector<int>>{
    shape(),
    other.shape()
  });
  std::vector<std::pair<float, float>> b = broadcast(other);
  std::vector<float> ans;
  for (std::pair<float, float> a: b) {
    ans.push_back(a.first + a.second);
  }
  tensor t = tensor(ans, out_shape);
  t.parents_.push_back(this);
  t.parents_.push_back(&other);
  return t;
}

// tensor tensor::operator+(float other) {
//   tensor* other_broadcast = new tensor(size_, other);
//   return *this + *other_broadcast;
// }

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

std::vector<std::pair<float, float>> tensor::broadcast(tensor& other) {
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

  std::vector<size_t> a = broadcast_to(*this, out_shape);
  std::vector<size_t> b = broadcast_to(other, out_shape);

  std::vector<std::pair<float, float>> ans;
  for (int i = 0; i < size; i++) {
    int a_idx = elem_to_loc(i, shape(), a);
    int b_idx = elem_to_loc(i, other.shape(), b);
    ans.push_back(std::pair<float, float>(data()[a_idx], other.data()[b_idx]));
  }
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

std::vector<size_t> tensor::broadcast_to(tensor& x, std::vector<int> shape) {
  if (x.shape() == shape) return x.data_.strides();

  int diff = shape.size() - x.size();
  std::vector<size_t> strides(shape.size(), 0);
  for (int i = x.shape().size() - 1; i >= 0; i--) {
    strides[i + diff] = x.shape()[i] == 1 ? 0 : x.data_.strides()[i];
  }

  return strides;
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
