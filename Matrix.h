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

    // Transforms a matrix into its transpose matrix
    Matrix& transpose();
    // Transforms a matrix into a column vector
    Matrix& vectorize();

    void plain_print() const; // Prints matrix elements, no return value
    // Returns a new Matrix that is the element-wise multiplication
    Matrix& dot(const Matrix& m) const;
    // (Hadamard product) of this matrix with another matrix m
    float norm() const; // Returns the Frobenius norm of the given matrix
    // Returns a new Matrix
    // that is the reduced row echelon form of the original
    Matrix rref() const;
    // Returns index (single-dimension index)
    // of the largest number in the matrix.
    int argmax() const;
    // Returns the sum of all the elements in the matrix
    float sum() const;

    // Operators
    Matrix& operator+=(const Matrix& m);
    Matrix& operator+(const Matrix& m) const;
    Matrix& operator=(const Matrix& m); // Assignment
    // Matrix multiplication
    Matrix& operator*(const Matrix& m) const;
    // Scalar multiplication on the right
    Matrix operator*(float c) const;
    // Scalar multiplication on the left
    friend Matrix operator*(int scalar, const Matrix& m);
    // Returns the value in cell (row, col)
    float operator()(int row, int col) const;
    // Returns reference for value in cell (row, col)
    float& operator()(int row, int col);
    // Returns the value of the cell in the index position
    float operator[](int index) const;
    float& operator[](int index); // Returns a reference for a cell
    // Pretty print of the matrix
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    // Fills matrix elements
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};


#endif //MATRIX_H