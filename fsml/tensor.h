#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>
#include <vector>

class operation;

class tensor {

public:
  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  tensor(int size, float* data, std::vector<int> shape);

  float* data();

  int size();

  std::vector<int> shape();

  tensor operator+(tensor& other);

  void backward();

  void create_graph();

  std::string repr();

  operation* ctx_;
  tensor* grad;
  std::vector<tensor*> parents_;

private:
  int size_;
  float* data_;
  std::vector<int> shape_;
};
#endif
