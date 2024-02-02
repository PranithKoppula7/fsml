#include "../tensor.h"
#include <gtest/gtest.h>

TEST(TensorTest, AddWithOneElement) {
  tensor::tensor a = tensor::tensor(1, 1);
  tensor::tensor b = tensor::tensor(1, 2);

  tensor::tensor c = a + b;

  EXPECT_EQ(c.data_[0], 3);
}
