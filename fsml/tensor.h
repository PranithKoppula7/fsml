#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>
#include <vector>

#include "buffer.h"
#include "buffer.cpp"

class operation;
class tensor;

/** 
 * pads dimensions with 1 from left to right
 * 
 * @param shapes 2d vector of type `int` (shapes of tensors to pad)
 * @return 2d vector of `int`, shapes padded with 1
*/
std::vector<std::vector<int>> pad_left(std::vector<std::vector<int>> shapes);
/**
 * returns the broadcast shape by finding max dimension for each dimension
 * 
 * @param shapes 2d vector of type `int` 
 * @return vector of `int` represnting the broadcast shape to be done
*/
std::vector<int> broadcast_shape(std::vector<std::vector<int>> shapes);


size_t elem_to_loc(int elem, std::vector<int> shape, std::vector<size_t> strides);

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

  operation* ctx_;
  tensor* grad;
  std::vector<tensor*> parents_;
  buffer<float> data_;
private:
  tensor broadcast_to(tensor& x, std::vector<int> shape);
  std::vector<float> data_vec;

};
#endif
