#include "lab01/matrix_ops.hpp"

#include <iostream>

namespace lab01 {

int** MatrixCreate(std::size_t rows, std::size_t cols) {
    if (cols == 0 || rows == 0) {
        return nullptr;
    }

    int** m = new int*[rows]();

    for (std::size_t i = 0; i < rows; ++i) {
        m[i] = new int[cols]();
    }

    return m;
}

bool TryMatrixDelete(int**& matrix, std::size_t rows) {
    if (matrix == nullptr) {
        return true;
    }

    if (rows == 0) {
        return false;
    }

    for (std::size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }

    delete[] matrix;
    matrix = nullptr;
    return true;
}

bool TryMatrixFill(int** m, std::size_t rows, std::size_t cols, int value) {
    if (m == nullptr) {
        return false;
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            m[i][j] = value;
        }
    }
    return true;
}

bool TryMatrixPrint(const int* const* m, std::size_t rows, std::size_t cols) {
    if (m == nullptr) {
        return false;
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            std::cout << m[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return true;
}

int* MatrixRowMax(const int* const* m, std::size_t rows, std::size_t cols) {
    if (m == nullptr) {
        return nullptr;
    }

    int* out = new int[rows];

    for (std::size_t i = 0; i < rows; ++i) {
        int max = m[i][0];

        for (std::size_t j = 0; j < cols; ++j) {
            if (m[i][j] > max) {
                max = m[i][j];
            }
        }

        out[i] = max;
    }

    return out;
}

int* MatrixColMin(const int* const* m, std::size_t rows, std::size_t cols) {
    if (m == nullptr) {
        return nullptr;
    }

    int* out = new int[cols];

    for (std::size_t j = 0; j < cols; ++j) {
        int min = m[0][j];

        for (std::size_t i = 0; i < rows; ++i) {
            if (m[i][j] < min) {
                min = m[i][j];
            }
        }

        out[j] = min;
    }

    return out;
}

}  // namespace lab01
