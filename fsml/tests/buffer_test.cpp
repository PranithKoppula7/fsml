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

TEST(BufferTest, InitializeNDShape) {
    std::vector<int> shape = {2, 3, 5, 10};
    buffer<float> b(shape);

    EXPECT_EQ(b.getShape(), std::vector<int>({2, 3, 5, 10}));
    EXPECT_EQ(b.getStrides(), std::vector<std::size_t>({600, 200, 40, 4}));
}

TEST(BufferTest, InitializeShapeContains0_Throws) {
    try {
        std::vector<int> shape = {1, 2, 0};
        buffer<float> b(shape);
    } catch(std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "Shape cannot contain 0");
    }
}