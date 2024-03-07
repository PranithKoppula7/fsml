#include "../tensor.h"

#include <gtest/gtest.h>
#include <vector>

TEST(TensorTest, ConstructorTestSizeOnly) {
  tensor a = tensor::tensor(10);

  float* data = a.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 0);
  }

  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.shape(), std::vector<int> {10});
}

TEST(TensorTest, ConstructorTestSizeAndValue) {
  tensor a = tensor::tensor(10, 1.0);

  float* data = a.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.shape(), std::vector<int> {10});
}

TEST(TensorTest, ConstructorTestSizeAndArray) {
  float d[3] = {1.0, 1.0, 1.0};
  tensor a = tensor::tensor(3, d);

  float* data = a.data();
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.shape(), std::vector<int> {3});
}

TEST(TensorTest, AddWithOneElement) {
  tensor a = tensor::tensor(1, 1);
  tensor b = tensor::tensor(1, 2);

  tensor c = a + b;

  float* data = c.data();
  EXPECT_EQ(data[0], 3);

  delete data;
}

TEST(TensorTest, AddWithManyElements) {
  tensor a = tensor::tensor(10, 5);
  tensor b = tensor::tensor(10, 10);

  tensor c = a + b;

  float* data = c.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 15);
  }

  delete data;
}

TEST(TensorTest, AddWithSpecificElements) {
  float a_data[] = {1.0, 2.0};
  float b_data[] = {2.0, 3.0};
  tensor a = tensor::tensor(2, a_data);
  tensor b = tensor::tensor(2, b_data);

  tensor c = a + b;

  float* data = c.data();

  EXPECT_EQ(c.size(), 2);
  EXPECT_EQ(data[0], 3.0);
  EXPECT_EQ(data[1], 5.0);

  delete data;
}