#include "tensor.h"
#include "../fsml/backend/tensor.cuh"
#include "operation.h"
#include "graph.h"

#include <cstddef>
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
  tensor t = Add->forward(*this, other);
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

// std::pair<tensor, tensor> tensor::broadcast(tensor& other) {
//   std::vector<int> out_shape = broadcast_shape(std::vector<std::vector<int>>{
//     shape_,
//     other.shape_
//   });
  
//   if (shape_.size() > out_shape.size()) {
//     throw std::runtime_error("Cannot broadcast tensor");
//   }

//   reshape* Reshape = new reshape();

//   tensor x = Reshape->forward(*this, out_shape);
//   tensor y = Reshape->forward(other, out_shape);

//   return std::pair<tensor, tensor>{x, y};
// }

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
