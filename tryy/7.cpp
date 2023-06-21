#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>

class TMatrix {
protected:
    int** matrix;
    int rows;
    int cols;

public:

    TMatrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
    }

    ~TMatrix() {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void setElement(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            matrix[row][col] = value;
        } else {
            throw std::runtime_error("Invalid matrix indices.");
        }
    }

    void printMatrix() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

class SquareMatrix : public TMatrix {
public:
    SquareMatrix(int size) : TMatrix(size, size) {}

    SquareMatrix operator+(const SquareMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrices have different sizes.");
        }

        SquareMatrix result(rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }

        return result;
    }

    
    SquareMatrix transpose() const {
        SquareMatrix result(rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.matrix[i][j] = matrix[j][i];
            }
        }

        return result;
    }
};

class ColumnMatrix : public TMatrix {
public:
    ColumnMatrix(int numRows) : TMatrix(numRows, 1) {}

    ColumnMatrix operator*(int scalar) const {
        ColumnMatrix result(rows);

        for (int i = 0; i < rows; i++) {
            result.matrix[i][0] = matrix[i][0] * scalar;
        }

        return result;
    }
};




int main() {
    // Встановлюємо seed для генератора випадкових чисел
    std::srand(std::time(nullptr));

    // Створюємо квадратну матрицю 3x3
    SquareMatrix matrix1(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix1.setElement(i, j, std::rand() % 10);
        }
    }

    
    std::cout << "Matrix 1:" << std::endl;
    matrix1.printMatrix();

    
    SquareMatrix transposedMatrix = matrix1.transpose();

    std::cout << "Transposed Matrix 1:" << std::endl;
    transposedMatrix.printMatrix();

    SquareMatrix matrix2(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix2.setElement(i, j, std::rand() % 10);
        }
    }

    std::cout << "Matrix 2:" << std::endl;
    matrix2.printMatrix();

    SquareMatrix sumMatrix = matrix1 + matrix2;


    std::cout << "Sum Matrix:" << std::endl;
    sumMatrix.printMatrix();

    ColumnMatrix columnMatrix(3);
    for (int i = 0; i < 3; i++) {
        columnMatrix.setElement(i, 0, std::rand() % 10);
    }

    std::cout << "Column Matrix:" << std::endl;
    columnMatrix.printMatrix();

    ColumnMatrix resultMatrix = columnMatrix * 5;

    std::cout << "Result Matrix:" << std::endl;
    resultMatrix.printMatrix();

    return 0;
}
