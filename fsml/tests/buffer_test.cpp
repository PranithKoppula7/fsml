#include "../buffer.h"
#include "../buffer.cpp"

#include <gtest/gtest.h>
#include <vector>

TEST(BufferTest, Initialize) {
    std::vector<int> shape = {1, 2};
    std::vector<float> a = {1.0, 2.0};

    buffer<float> b(shape, a);

    EXPECT_EQ(b.getShape(), std::vector<int>({1, 2}));
    EXPECT_EQ(b.getStrides(), std::vector<std::size_t>({8, 4}));
    EXPECT_EQ(b.getData(), a);
}

TEST(BufferTest, Initialize3DShape) {
    std::vector<int> shape = {1, 2, 3};
    std::vector<float> a = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    buffer<float> b(shape, a);

    EXPECT_EQ(b.getShape(), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(b.getStrides(), std::vector<std::size_t>({24, 12, 4}));
    EXPECT_EQ(b.getData(), a);
}

TEST(BufferTest, InitializeNDShape) {
    std::vector<int> shape = {2, 3, 5, 10};
    std::vector<float> a(300, 1.0);

    buffer<float> b(shape, a);

    EXPECT_EQ(b.getShape(), std::vector<int>({2, 3, 5, 10}));
    EXPECT_EQ(b.getStrides(), std::vector<std::size_t>({600, 200, 40, 4}));
    EXPECT_EQ(b.getData(), a);
}

TEST(BufferTest, InitializeShapeContains0_Throws) {
    try {
        std::vector<int> shape = {1, 2, 0};
        std::vector<float> a = {1, 2};
        buffer<float> b(shape, a);
    } catch(std::invalid_argument e) {
        EXPECT_STREQ(e.what(), "Shape cannot contain 0");
    }
}

TEST(BufferTest, IndexingGeneral) {
    std::vector<int> shape = {1, 2};
    std::vector<float> a = {1.0, 2.0};

    buffer<float> b(shape, a);
    float i = b.get(std::vector<int>{0, 0});

    EXPECT_EQ(i, 1.0);
}