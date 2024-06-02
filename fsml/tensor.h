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

class tensor {

public:

  tensor(std::vector<float> data, std::vector<int> shape);

  float* data();

  int size();

  std::vector<int> shape();

  /* add op */
  tensor operator+(tensor& other);
  tensor operator+(float other);

  void backward();

  void create_graph();

  std::string repr();

  operation* ctx_;
  tensor* grad;
  std::vector<tensor*> parents_;
private:
  buffer<float> data_;

};
#endif
