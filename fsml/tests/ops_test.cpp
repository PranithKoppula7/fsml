#include "../tensor.h"
#include <iostream>

int main() {
  tensor::tensor a = tensor::tensor(1, 1);
  tensor::tensor b = tensor::tensor(1, 2);

  tensor::tensor c = a + b;

  std::cout << c.data_[0] << std::endl;
}
