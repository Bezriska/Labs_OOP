#include <cstddef>
#include <iostream>
#include <limits>

#include "lab01/matrix_ops.hpp"

int main() {
    int user_input{};
    bool is_matrix_exist{false};

    int** m{};
    std::size_t rows{};
    std::size_t cols{};

    while (true) {
        std::cout << "\nChoose one operation and print its number:\n1. Make matrix\n2. Fill with one "
                     "value\n3. Print\n4. Print min from each cols\n5. Delete matrix\n6. Write one value\n7. Print max "
                     "from each row\n0. Exit\n";

        if (!(std::cin >> user_input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error\n";
            continue;
        }

        switch (user_input) {
            case 0: {
                if (!is_matrix_exist) {
                    std::cout << "Exit...\n";
                    return 0;
                }

                if (!lab01::TryMatrixDelete(m, rows)) {
                    std::cout << "Error in matrix deleting, do you trust GC? (1/0)\n";

                    int resp{};
                    if (!(std::cin >> resp)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Input error\n";
                    }

                    while (resp != 1 && resp != 0) {
                        std::cout << "Bro, write 1 or 0 :(\n";

                        if (!(std::cin >> resp)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Input error\n";
                        }
                    }

                    if (resp == 1) {
                        std::cout << "Exit...\n";
                        return 0;
                    } else {
                        std::cout << "Try delete again\n";
                        break;
                    }
                }

                std::cout << "Exit...\n";
                return 0;
            }

            case 1: {
                int raw_rows{};
                int raw_cols{};
                std::cout << "Print size of matrix (rows cols):\n";
                if (!(std::cin >> raw_rows >> raw_cols) || raw_cols < 0 || raw_rows < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Input error\n";
                    break;
                }

                cols = static_cast<std::size_t>(raw_cols);
                rows = static_cast<std::size_t>(raw_rows);

                m = lab01::MatrixCreate(rows, cols);
                is_matrix_exist = true;
                std::cout << "Matrix was created\n";
                break;
            }

            case 2: {
                if (!is_matrix_exist) {
                    std::cout << "Error, you need to create matrix first\n";
                    break;
                }

                int value{};

                std::cout << "Print value:\n";
                if (!(std::cin >> value)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Input error\n";
                    break;
                }

                if (lab01::TryMatrixFill(m, rows, cols, value)) {
                    std::cout << "Matrix succesfully filled\n";
                    break;
                } else {
                    std::cout << "Error in filling matrix\n";
                    break;
                }

                break;
            }

            case 3: {
                if (!is_matrix_exist) {
                    std::cout << "Error, you need to create matrix first\n";
                    break;
                }

                if (lab01::TryMatrixPrint(m, rows, cols)) {
                    std::cout << "Matrix succesfully printed\n";
                    break;
                } else {
                    std::cout << "Error in printing matrix\n";
                    break;
                }

                break;
            }

            case 4: {
                if (!is_matrix_exist) {
                    std::cout << "Error, you need to create matrix first\n";
                    break;
                }

                int* mins = lab01::MatrixColMin(m, rows, cols);

                std::cout << "Min from each col:\n";
                for (std::size_t i = 0; i < cols; ++i) {
                    std::cout << mins[i] << ' ';
                }
                break;
            }

            case 5: {
                if (!is_matrix_exist) {
                    std::cout << "Matrix already does not exist\n";
                    break;
                }

                if (!lab01::TryMatrixDelete(m, rows)) {
                    std::cout << "Error in deleting matrix\n";
                    break;
                }

                std::cout << "Matrix was succesfully deleted";
                is_matrix_exist = false;
                break;
            }

            case 6: {
                if (!is_matrix_exist) {
                    std::cout << "Error, you need to create matrix first\n";
                    break;
                }

                std::cout << "Write row, col and value:\n";

                int raw_row{};
                int raw_col{};
                int value{};
                if (!(std::cin >> raw_row >> raw_col >> value) || raw_col <= 0 || raw_row <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Input error\n";
                    break;
                }

                raw_row -= 1;
                raw_col -= 1;

                std::size_t row{};
                std::size_t col{};

                row = static_cast<std::size_t>(raw_row);
                col = static_cast<std::size_t>(raw_col);

                if (row > rows || col > cols) {
                    std::cout << "Error, index must be in range\n";
                    break;
                }

                m[row][col] = value;
                std::cout << "Value was added\n";
                break;
            }

            case 7: {
                if (!is_matrix_exist) {
                    std::cout << "Error, you need to create matrix first\n";
                    break;
                }

                int* maxs = lab01::MatrixRowMax(m, rows, cols);

                std::cout << "Max from each row:\n";
                for (std::size_t i = 0; i < rows; ++i) {
                    std::cout << maxs[i] << ' ';
                }

                break;
            }

            default: {
                std::cout << "This number does not exist\n";
                break;
            }
        }
    }
}

/*
    cmake -S . -B build -DCMAKE_CXX_COMPILER=g++-16
    cmake --build build -j

    ctest --test-dir build --output-on-failure
*/