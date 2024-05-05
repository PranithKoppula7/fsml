#include "../tensor.h"

#include <gtest/gtest.h>
#include <vector>

TEST(TensorTest, ConstructorTestSizeOnly) {
  tensor a = tensor(10);

  float* data = a.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 0);
  }

  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.shape(), std::vector<int> {10});
}

TEST(TensorTest, ConstructorTestSizeAndValue) {
  tensor a = tensor(10, 1.0);

  float* data = a.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.shape(), std::vector<int> {10});
}

TEST(TensorTest, ConstructorTestSizeAndArray) {
  float d[3] = {1.0, 1.0, 1.0};
  tensor a = tensor(3, d);

  float* data = a.data();
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.shape(), std::vector<int> {3});
}

TEST(TensorTest, ConstructorTestSizeAndArrayAndShape) {
  float d[3] = {1.0, 1.0, 1.0};
  tensor a = tensor(3, d, std::vector<int>{3});

  float* data = a.data();
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(data[i], 1.0);
  }

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.shape(), std::vector<int> {3});
}

TEST(TensorTest, ConstructorTestSizeAndArrayAndShapeIncorrect) {
  try {
    float d[3] = {1.0, 1.0, 1.0};
    tensor a = tensor(3, d, std::vector<int>{2});
  } catch (std::runtime_error e) {
    EXPECT_STREQ("shape does not match size", e.what());
  }
}

TEST(TensorTest, AddTensorWithOneElement) {
  tensor a = tensor(1, 1);
  tensor b = tensor(1, 2);

  tensor c = a + b;

  float* data = c.data();
  EXPECT_EQ(data[0], 3);

  delete data;
}

TEST(TensorTest, AddTensorWithManyElements) {
  tensor a = tensor(10, 5);
  tensor b = tensor(10, 10);

  tensor c = a + b;

  float* data = c.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 15);
  }

  delete data;
}

TEST(TensorTest, AddTensorWithSpecificElements) {
  float a_data[] = {1.0, 2.0};
  float b_data[] = {2.0, 3.0};
  tensor a = tensor(2, a_data);
  tensor b = tensor(2, b_data);

  tensor c = a + b;

  float* data = c.data();

  EXPECT_EQ(c.size(), 2);
  EXPECT_EQ(data[0], 3.0);
  EXPECT_EQ(data[1], 5.0);

  delete data;
}

TEST(TensorTest, AddTensorBackward) {
  float a_data[] = {1.0, 2.0};
  float b_data[] = {2.0, 3.0};
  tensor a = tensor(2, a_data);
  tensor b = tensor(2, b_data);

  tensor c = a + b;

  c.backward();
  float* a_grad = a.grad->data();
  float* b_grad = b.grad->data();
  float* c_grad = c.grad->data();

  EXPECT_EQ(c.size(), 2);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(a_grad[i], 1.0);
    EXPECT_EQ(b_grad[i], 1.0);
    EXPECT_EQ(c_grad[i], 1.0);
  }
}

TEST(TensorTest, AddFloat) {
  float a_data[] = {1.0, 2.0};
  tensor a = tensor(2, a_data);

  tensor b = a + 1.0;
  float* data = b.data();

  EXPECT_EQ(data[0], 2.0);
  EXPECT_EQ(data[1], 3.0);
}

TEST(TensorTest, BroadcastInvalidShapesThrowsError) {
  float a_data[] = {1.0, 2.0};
  float b_data[] = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  tensor a = tensor(2, a_data);
  tensor b = tensor(6, b_data, std::vector<int>{2, 3});

  try {
    tensor c = a + b;
  } catch (std::runtime_error e) {
    EXPECT_STREQ("shapes are not broadcastable", e.what());
  }
}

TEST(TensorTest, PadLeftGeneral) {
  std::vector<int> a = {2};
  std::vector<int> b = {2, 3};
  std::vector<std::vector<int>> expected = std::vector<std::vector<int>>{
    std::vector<int>{1, 2},
    std::vector<int>{2, 3}
  };

  std::vector<std::vector<int>> ans = pad_left(
    std::vector<std::vector<int>>{a, b});

  EXPECT_EQ(ans.size(), 2);
  EXPECT_EQ(ans, expected);
}

TEST(TensorTest, PadLeftReturnsSame) {
  std::vector<int> a = {1, 2};
  std::vector<int> b = {2, 3};
  std::vector<std::vector<int>> expected = std::vector<std::vector<int>>{
    std::vector<int>{1, 2},
    std::vector<int>{2, 3}
  };

  std::vector<std::vector<int>> ans = pad_left(
    std::vector<std::vector<int>>{a, b});

  EXPECT_EQ(ans.size(), 2);
  EXPECT_EQ(ans, expected);
}

TEST(TensorTest, PadLeft3dMultiple) {
  std::vector<int> a = {2};
  std::vector<int> b = {2, 3};
  std::vector<int> c = {2, 2};
  std::vector<int> d = {1, 1, 3};
  std::vector<std::vector<int>> expected = std::vector<std::vector<int>>{
    std::vector<int>{1, 1, 2},
    std::vector<int>{1, 2, 3},
    std::vector<int>{1, 2, 2},
    std::vector<int>{1, 1, 3}
  };

  std::vector<std::vector<int>> ans = pad_left(
    std::vector<std::vector<int>>{a, b, c, d});

  EXPECT_EQ(ans.size(), 4);
  EXPECT_EQ(ans, expected);
}

TEST(TensorTest, BroadcastShapeGeneral) {
  std::vector<std::vector<int>> input = std::vector<std::vector<int>>{{
    std::vector<int>{2},
    std::vector<int>{1, 2},
    std::vector<int>{1, 2, 3},
  }};
  std::vector<int> expected = std::vector<int>{1, 2, 3};

  std::vector<int> ans = broadcast_shape(input);

  EXPECT_EQ(ans.size(), 3);
  EXPECT_EQ(ans, expected);
}

TEST(TensorTest, BroadcastShapeReturnsEmpty) {
  std::vector<int> ans = broadcast_shape(std::vector<std::vector<int>>{});
  EXPECT_EQ(ans, std::vector<int>{});
}