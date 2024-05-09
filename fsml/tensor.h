#pragma once
#ifndef FSML_TENSOR_H
#define FMSL_TENSOR_H

#include <string>
#include <vector>

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

  tensor(int size);

  tensor(int size, float value);  

  tensor(int size, float* data);

  tensor(int size, float* data, std::vector<int> shape);

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
  int size_;
  float* data_;
  std::vector<int> shape_;

};
#endif
