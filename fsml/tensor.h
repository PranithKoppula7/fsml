#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>
#include <vector>

#include "buffer.h"
#include "buffer.cpp"

class operation;
class tensor;

class tensor {

public:

  tensor(std::vector<float> data, std::vector<int> shape);

  tensor(buffer<float> b): data_(b) {}

  float* data();

  int size();

  std::vector<int> shape();

  /* add op */
  tensor operator+(tensor& other);
  tensor operator+(float other);

  void backward();

  void create_graph();

  std::string repr();


  std::pair<std::vector<float>, std::vector<float>> broadcast(tensor& a, tensor& b);
  tensor broadcast(tensor& a, std::vector<int> shape);

  operation* ctx_;
  tensor* grad;
  std::vector<tensor*> parents_;
  buffer<float> data_;
  std::vector<float> data_vec;
private:
  tensor broadcast_to(tensor& x, std::vector<int> shape);

};
#endif
