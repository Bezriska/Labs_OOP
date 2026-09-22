#include "lab01/matrix_ops.hpp"

#include <vector>

#include <gtest/gtest.h>

namespace lab01 {
namespace {

int** MakeMatrix(const std::vector<std::vector<int>>& values) {
    std::size_t rows = values.size();
    std::size_t cols = values.empty() ? 0 : values[0].size();
    int** m = MatrixCreate(rows, cols);
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            m[i][j] = values[i][j];
        }
    }
    return m;
}

TEST(MatrixCreateTest, ReturnsNonNullForValidSize) {
    int** m = MatrixCreate(3, 4);
    ASSERT_NE(m, nullptr);
    TryMatrixDelete(m, 3);
}

TEST(MatrixCreateTest, ElementsAreZeroInitialized) {
    int** m = MatrixCreate(2, 2);
    ASSERT_NE(m, nullptr);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[0][1], 0);
    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[1][1], 0);
    TryMatrixDelete(m, 2);
}

TEST(MatrixCreateTest_Fail, ReturnsNullptrForZeroRows) {
    int** m = MatrixCreate(0, 4);
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixCreateTest_Fail, ReturnsNullptrForZeroCols) {
    int** m = MatrixCreate(4, 0);
    EXPECT_EQ(m, nullptr);
}

TEST(TryMatrixFillTest, FillsEveryElementWithValue) {
    int** m = MatrixCreate(3, 3);
    ASSERT_TRUE(TryMatrixFill(m, 3, 3, 7));

    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            EXPECT_EQ(m[i][j], 7);
        }
    }

    TryMatrixDelete(m, 3);
}

TEST(TryMatrixFillTest, WorksOnRectangularMatrix) {
    int** m = MatrixCreate(2, 5);
    ASSERT_TRUE(TryMatrixFill(m, 2, 5, -1));

    for (std::size_t i = 0; i < 2; ++i) {
        for (std::size_t j = 0; j < 5; ++j) {
            EXPECT_EQ(m[i][j], -1);
        }
    }

    TryMatrixDelete(m, 2);
}

TEST(TryMatrixFillTest_Fail, ReturnsFalseForNullptr) {
    int** m = nullptr;
    EXPECT_FALSE(TryMatrixFill(m, 3, 3, 5));
}

TEST(TryMatrixDeleteTest, ReturnsTrueAndNullsPointerForNullptrInput) {
    int** m = nullptr;
    EXPECT_TRUE(TryMatrixDelete(m, 3));
    EXPECT_EQ(m, nullptr);
}

TEST(TryMatrixDeleteTest, NullsCallerPointerAfterDeletion) {
    int** m = MatrixCreate(2, 2);
    ASSERT_NE(m, nullptr);
    EXPECT_TRUE(TryMatrixDelete(m, 2));
    EXPECT_EQ(m, nullptr);
}

TEST(TryMatrixDeleteTest_Fail, ReturnsFalseForZeroRowsWithNonNullMatrix) {
    int** m = MatrixCreate(2, 2);
    EXPECT_FALSE(TryMatrixDelete(m, 0));
    TryMatrixDelete(m, 2);
}

TEST(TryMatrixPrintTest_Fail, ReturnsFalseForNullptr) {
    EXPECT_FALSE(TryMatrixPrint(nullptr, 3, 3));
}

TEST(MatrixRowMaxTest, ComputesMaxOfEachRow) {
    int** m = MakeMatrix({{1, 5, 3}, {9, 2, 4}, {-1, -5, -3}});
    int* result = MatrixRowMax(m, 3, 3);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 9);
    EXPECT_EQ(result[2], -1);

    delete[] result;
    TryMatrixDelete(m, 3);
}

TEST(MatrixRowMaxTest, WorksOnRectangularMatrix) {
    int** m = MakeMatrix({{1, 2, 3, 4}, {8, 7, 6, 5}});
    int* result = MatrixRowMax(m, 2, 4);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 4);
    EXPECT_EQ(result[1], 8);

    delete[] result;
    TryMatrixDelete(m, 2);
}

TEST(MatrixRowMaxTest_Fail, ReturnsNullptrForNullptr) {
    EXPECT_EQ(MatrixRowMax(nullptr, 3, 3), nullptr);
}

TEST(MatrixColMinTest, ComputesMinOfEachColumn) {
    int** m = MakeMatrix({{1, 5, 3}, {9, 2, 4}, {-1, -5, -3}});
    int* result = MatrixColMin(m, 3, 3);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -5);
    EXPECT_EQ(result[2], -3);

    delete[] result;
    TryMatrixDelete(m, 3);
}

TEST(MatrixColMinTest, WorksOnRectangularMatrix) {
    int** m = MakeMatrix({{1, 8}, {2, 7}, {3, 6}});
    int* result = MatrixColMin(m, 3, 2);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 6);

    delete[] result;
    TryMatrixDelete(m, 3);
}

TEST(MatrixColMinTest_Fail, ReturnsNullptrForNullptr) {
    EXPECT_EQ(MatrixColMin(nullptr, 3, 3), nullptr);
}

}  // namespace
}  // namespace lab01