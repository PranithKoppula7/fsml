#include "../buffer.h"
#include "../buffer.cpp"

#include <gtest/gtest.h>
#include <vector>

TEST(BufferTest, Initialize) {
    std::vector<int> shape = {1, 2};
    std::vector<float> a = {1.0, 2.0};
    float expected[2] = {1.0, 2.0};

    buffer<float> b(shape, a);

    EXPECT_EQ(b.shape(), std::vector<int>({1, 2}));
    EXPECT_EQ(b.strides(), std::vector<std::size_t>({8, 4}));
    for (int i = 0; i < 2; i++) EXPECT_EQ(b.data()[i], expected[i]);

}

TEST(BufferTest, Initialize3DShape) {
    std::vector<int> shape = {1, 2, 3};
    std::vector<float> a = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    float expected[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    buffer<float> b(shape, a);

    EXPECT_EQ(b.shape(), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(b.strides(), std::vector<std::size_t>({24, 12, 4}));
    for (int i = 0; i < 6; i++) EXPECT_EQ(b.data()[i], expected[i]);
}

TEST(BufferTest, InitializeNDShape) {
    std::vector<int> shape = {2, 3, 5, 10};
    std::vector<float> a(300, 1.0);
    float expected[300];
    for (int i = 0; i < 300; i++) expected[i] = 1.0;

    buffer<float> b(shape, a);

    EXPECT_EQ(b.shape(), std::vector<int>({2, 3, 5, 10}));
    EXPECT_EQ(b.strides(), std::vector<std::size_t>({600, 200, 40, 4}));
    for (int i = 0; i < 300; i++) EXPECT_EQ(b.data()[i], expected[i]);
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
    float j = b.get(std::vector<int>{0, 1});

    EXPECT_EQ(i, 1.0);
    EXPECT_EQ(j, 2.0);
}

TEST(BufferTest, IndexingAndSetting) {
    std::vector<int> shape = {2, 3, 5, 10};
    std::vector<float> a(300, 1.0);

    buffer<float> b(shape, a);
    b.set(std::vector<int>{1, 2, 3, 4}, 2.0);

    EXPECT_EQ(b.get(std::vector<int>{1, 2, 3, 4}), 2.0);
    EXPECT_EQ(b.get(std::vector<int>{1, 2, 4, 9}), 1.0);
}