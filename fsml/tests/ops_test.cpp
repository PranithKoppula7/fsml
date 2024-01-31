#include "../tensor.h"

int main() {
  tensor::tensor a = tensor::tensor(1);
  tensor::tensor b = tensor::tensor(1, 2);

  tensor::tensor c = a + b;
}
