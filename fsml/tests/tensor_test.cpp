#include "../tensor.h"

#include <gtest/gtest.h>
#include <vector>

TEST(TensorTest, ConstructorSimple) {
  tensor a = tensor(std::vector<float>{1.0}, std::vector<int>{1});
  float expected[] = {1.0};

  EXPECT_EQ(a.data()[0], expected[0]);
  EXPECT_EQ(a.shape(), std::vector<int>{1});
  EXPECT_EQ(a.size(), 1);
}

TEST(TensorTest, Constructor3DShape) {
  std::vector<float> data = std::vector<float>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  std::vector<int> shape = std::vector<int>{1, 2, 3};
  tensor a = tensor(data, shape);
  float expected[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  float* actual = a.data();

  for (int i = 0; i < a.size(); i++) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}
TEST(TensorTest, AddTensorWithOneElement) {
  std::vector<float> data = std::vector<float>{1.0};
  std::vector<int> shape = std::vector<int>{1};
  tensor a = tensor(data, shape);
  tensor b = tensor(data, shape);

  tensor c = a + b;

  float* d = c.data();
  EXPECT_EQ(d[0], 2.0);

}

TEST(TensorTest, AddTensorWithManyElements) {
  std::vector<float> data1 = std::vector<float>(10, 10.0);
  std::vector<float> data2 = std::vector<float>(10, 5.0);
  std::vector<int> shape = std::vector<int>{10};
  tensor a = tensor(data1, shape);
  tensor b = tensor(data2, shape);

  tensor c = a + b;

  float* data = c.data();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(data[i], 15.0);
  }
}

TEST(TensorTest, AddTensorWithSpecificElements) {
  std::vector<float> a_data{1.0, 2.0};
  std::vector<float> b_data{2.0, 3.0};
  std::vector<int> shape = std::vector<int>{2};
  tensor a = tensor(a_data, shape);
  tensor b = tensor(b_data, shape);

  tensor c = a + b;

  float* data = c.data();

  EXPECT_EQ(c.size(), 2);
  EXPECT_EQ(data[0], 3.0);
  EXPECT_EQ(data[1], 5.0);

}

TEST(TensorTest, AddTensorBackward) {
  std::vector<float> a_data{1.0, 2.0};
  std::vector<float> b_data{2.0, 3.0};
  std::vector<int> shape = std::vector<int>{2};
  tensor a = tensor(a_data, shape);
  tensor b = tensor(b_data, shape);

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

// TODO: fix test after implementing float add
// TEST(TensorTest, AddFloat) {
//   float a_data[] = {1.0, 2.0};
//   tensor a = tensor(2, a_data);

//   tensor b = a + 1.0;
//   float* data = b.data();

//   EXPECT_EQ(data[0], 2.0);
//   EXPECT_EQ(data[1], 3.0);
// }

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