#pragma once

#include <vector>

namespace tensor {

class tensor {

public:

  // empty initalization (randomly initialized)
  tensor(int size);

  // with a single value
  tensor(int size, float value);  

  ~tensor();

  tensor operator+(const tensor& other) const;

private:
  int size_;
  std::vector<float> data_;
};

} // namespace tensor
