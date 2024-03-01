#include "../tensor.h"

#include <gtest/gtest.h>
#include <vector>

TEST(TensorTest, ConstructorTestSizeOnly) {
  tensor::tensor a = tensor::tensor(10);

  float* data = a.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 0);
  }

  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.shape(), std::vector<int> {10});
}

TEST(TensorTest, ConstructorTestSizeAndValue) {
  tensor::tensor a = tensor::tensor(10, 1.0);

  float* data = a.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.shape(), std::vector<int> {10});
}

TEST(TensorTest, ConstructorTestSizeAndArray) {
  float d[3] = {1.0, 1.0, 1.0};
  tensor::tensor a = tensor::tensor(3, d);

  float* data = a.data();
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.shape(), std::vector<int> {3});
}

TEST(TensorTest, AddWithOneElement) {
  tensor::tensor a = tensor::tensor(1, 1);
  tensor::tensor b = tensor::tensor(1, 2);

  tensor::tensor c = a + b;

  float* data = c.data();
  EXPECT_EQ(data[0], 3);

  delete data;
}

TEST(TensorTest, AddWithManyElements) {
  tensor::tensor a = tensor::tensor(10, 5);
  tensor::tensor b = tensor::tensor(10, 10);

  tensor::tensor c = a + b;

  float* data = c.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 15);
  }

  delete data;
}