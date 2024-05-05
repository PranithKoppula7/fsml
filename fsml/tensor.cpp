#include "tensor.h"
#include "../fsml/backend/tensor.cuh"
#include "operation.h"
#include "graph.h"

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
  ctx_ = NULL;
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

  if (size_ > 1) shape_.push_back(size);
  ctx_ = NULL;
}

tensor::tensor(int size, float* data): size_(size) {
  size_t nBytes = size * sizeof(float);
  data_ = (float*)malloc(nBytes);
  for (int i = 0; i < size; i++) {
    data_[i] = data[i];
  }
  if (size_ > 1) shape_.push_back(size);
  ctx_ = NULL;
}

tensor::tensor(int size, float* data, std::vector<int> shape):
  size_(size), shape_(shape) {

  int shapeTotal = 1;
  for (int s: shape_) {
    shapeTotal *= s;
  }

  if (shapeTotal != size_) {
    throw std::runtime_error("shape does not match size");
  }
  
  size_t nBytes = size * sizeof(float);
  data_ = (float*)malloc(nBytes);
  for (int i = 0; i < size; i++) {
    data_[i] = data[i];
  }
  ctx_ = NULL;
}

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

tensor tensor::operator+(tensor& other) {
  tensor& other_bc = broadcast(other);
  operation* Add = new add();
  tensor t = Add->forward(*this, other_bc);
  t.parents_.push_back(this);
  t.parents_.push_back(&other_bc);
  return t;
}

tensor tensor::operator+(float other) {
  tensor* other_broadcast = new tensor(size_, other);
  return *this + *other_broadcast;
}

void tensor::backward() {
  grad = new tensor(size_, 1.0);
  ctx_->backward(*this);
}

void tensor::create_graph() {
  graph::run(*this);
}

tensor& tensor::broadcast(tensor& other) {
  // shape matches exactly
  if (shape_.size() == other.shape_.size() && shape_ == other.shape_) {
    return other;
  }

  if (shape_.size() < other.shape_.size()) {
    int j = other.shape_.size() - 1;
    for (int i = shape_.size() - 1; i >= 0; i--) {
      if (shape_[i] != other.shape_[j] &&
          (shape_[i] != 1 || other.shape_[j] != 1)) {
        throw std::runtime_error("shapes are not broadcastable");
      }
      j--;
    }
    
  }

  if (other.shape_.size() < shape_.size()) {
    int j = shape_.size() - 1;
    for (int i = other.shape_.size() - 1; i >= 0; i--) {
      if (other.shape_[i] != shape_[j] && 
          (other.shape_[i] != 1 || shape_[j] != 1)) {
        throw std::runtime_error("shapes are not broadcastable");
      }
      j--;
    }

  }

  return other;
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
  s += "]>\n";
  return s;
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
