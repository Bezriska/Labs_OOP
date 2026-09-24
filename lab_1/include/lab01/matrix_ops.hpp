#pragma once

#include <cstddef>

namespace lab01 {

int** MatrixCreate(std::size_t rows, std::size_t cols);

bool TryMatrixDelete(int**& matrix, std::size_t rows);

bool TryMatrixFill(int** m, std::size_t rows, std::size_t cols, int value);

bool TryMatrixPrint(const int* const* m, std::size_t rows, std::size_t cols);

int* MatrixRowMax(const int* const* m, std::size_t rows, std::size_t cols);

int* MatrixColMin(const int* const* m, std::size_t rows, std::size_t cols);

}
