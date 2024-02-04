#include "../tensor.h"
#include <gtest/gtest.h>

TEST(TensorTest, AddWithOneElement) {
  tensor::tensor a = tensor::tensor(1, 1);
  tensor::tensor b = tensor::tensor(1, 2);

  tensor::tensor c = a + b;

  EXPECT_EQ(c.data_[0], 3);
}

TEST(TensorTest, AddWithManyElements) {
  tensor::tensor a = tensor::tensor(10, 5);
  tensor::tensor b = tensor::tensor(10, 10);

  tensor::tensor c = a + b;

  for(int i = 0; i < 10; i++) {
    EXPECT_EQ(c.data_[i], 15);
  }
}
