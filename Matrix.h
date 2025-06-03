// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};

// Matrix class
class Matrix
{
private:
    matrix_dims* _dims; // Dimensions struct
    float* _values; // A pointer to the array of the values of the matrix

public:
    // Constructors
    Matrix(int rows, int cols); // Constructs Matrix of size rows X cols
    Matrix(); // Default constructor
    Matrix(const Matrix &m); // Copy constructor
    // Destructor
    ~Matrix(); // Release all resources owned by the class

    int get_rows() const; // Returns the number of rows
    int get_cols() const; // Returns the number of columns

    Matrix& transpose(); // Transforms a matrix into its transpose matrix
    Matrix& vectorize(); // Transforms a matrix into a column vector

    void plain_print() const; // Prints matrix elements, no return value
    Matrix& dot(const Matrix& m) const; // Returns a new Matrix that is the element-wise multiplication
    // (Hadamard product) of this matrix with another matrix m
    float norm() const; // Returns the Frobenius norm of the given matrix
    Matrix& rref() const; // Returns a new Matrix that is the reduced row echelon form of the original
    int argmax() const; // Returns index (single-dimension index) of the largest number in the matrix.
    float sum() const; // Returns the sum of all the elements in the matrix

    // Operators
    Matrix& operator+=(const Matrix& m);
    Matrix& operator+(const Matrix& m) const;
    Matrix& operator=(const Matrix& m); // Assignment
    Matrix& operator*(const Matrix& m) const; // Matrix multiplication
    Matrix& operator*(float c); // Scalar multiplication on the right
    friend Matrix& operator*(int scalar, Matrix& m); // Scalar multiplication on the left
    float operator()(int row, int col) const; // Returns the value in cell (row, col)
    float operator[](int index) const; // Returns the value of the cell in the index position
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m); // Pretty print of the matrix
    friend std::ifstream& operator>>(std::ifstream& is, Matrix& m); // Fills matrix elements
};


#endif //MATRIX_H