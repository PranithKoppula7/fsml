#include "../buffer.h"
#include "../buffer.cpp"

#include <gtest/gtest.h>
#include <vector>

TEST(BufferTest, Initialize) {
    std::vector<int> shape = {1, 2};
    buffer<float> b(shape);

    EXPECT_EQ(b.getShape(), std::vector<int>({1, 2}));
    EXPECT_EQ(b.getStrides(), std::vector<std::size_t>({8, 4}));
}

TEST(BufferTest, Initialize3DShape) {
    std::vector<int> shape = {1, 2, 3};
    buffer<float> b(shape);

    EXPECT_EQ(b.getShape(), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(b.getStrides(), std::vector<std::size_t>({24, 12, 4}));
}