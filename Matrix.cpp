//
// Created by dolev on 03/06/2025.
//

#include "Matrix.h"
#include <algorithm>
#include <iostream>
#include <cmath>

// Constructor
Matrix::Matrix(int row, int col)
{
    _dims = new matrix_dims(row, col);
    _values = new float[row * col];
    for (int i = 0; i < row * col; i++)
        _values[i] = 0;
}

// Void constructor
Matrix::Matrix()
{
    matrix_dims* dims = new matrix_dims();
    _values = new float[1*1];
    _values[0] = 0;
}

// Copy constructor
Matrix::Matrix(const Matrix& m)
{
    _dims = new matrix_dims(m._dims->rows, m._dims->cols);
    _values = new float[(_dims->rows)*(_dims->cols)];
    for (int i = 0; i < _dims->rows * _dims->cols; i++)
        _values[i] = m._values[i];
}

// Destructor
Matrix::~Matrix()
{
    delete _dims;
    delete[] _values;
}

// Getters
int Matrix::get_rows() const
{
    return _dims->rows;
}
int Matrix::get_cols() const
{
    return _dims->cols;
}

// Transpose
Matrix& Matrix::transpose()
{
    // Copying the values to a temporary list, by order of transposition
    // (r, c) -> (c, r)
    auto temp = new float[_dims->rows * _dims->cols];
    for (int r = 0; r < _dims->rows; r++)
        for (int c = 0; c < _dims->cols; c++)
            temp[c*_dims->rows + r] = _values[r*_dims->cols + c];

    // Copying from temp to the matrix in the same order
    for (int i = 0; i < _dims->cols * _dims->rows; i++)
        _values[i] = temp[i];

    std::swap(_dims->cols, _dims->rows);

    delete[] temp;
    return *this;
}

// Vectorize
Matrix& Matrix::vectorize()
{
    return *this;
}

// Plain print
void Matrix::plain_print() const
{
    for (int r = 0 ; r < _dims->rows; r++)
    {
        for (int c = 0; c < _dims->cols; c++)
            std::cout << _values[r*_dims->cols + c] << " ";
        std::cout << std::endl;
    }
}

Matrix& Matrix::dot(const Matrix& m) const
{
    if ((_dims->cols != m._dims->cols) || (_dims->rows != m._dims->rows))
    {
        auto trashMatrix = new Matrix();
        return *trashMatrix;
    }

    auto newMat = new Matrix(_dims->rows, _dims->cols);
    for (int i = 0; i < _dims->rows * _dims->cols; i++)
        newMat->_values[i] = _values[i] * m._values[i];

    return *newMat;
}

// Returns the Frobenius norm of the given matrix
float Matrix::norm() const
{
    float sum = 0;
    for (int i = 0; i < _dims->rows * _dims->cols; i++)
        sum += pow(_values[i], 2);
    return sqrt(sum);
}

// Returns a new Matrix that is the reduced row echelon form of the original
Matrix& Matrix::rref() const
{
    auto rrefMatrix = new Matrix(*this);

    // Counter of lead values
    int leads = 0;
    // For the maximum possible number of leading values
    for (int c = 0; c < std::min(_dims->cols, _dims->rows); c++)
    {
        for (int r = leads; r < _dims->rows; r++)
        {
            // Finding the first non-zero value of the current column
            if ((*rrefMatrix)(r, c) != 0)
            {
                // Swapping the whole row to the right one
                for (int i = 0; i < _dims->cols; i++)
                    std::swap(rrefMatrix->_values[r*_dims->cols + i], rrefMatrix->_values[leads*_dims->cols + i]);

                // Dividing the row by the value
                float divider = 1.0 / (*rrefMatrix)(leads, c);

                // Row division
                for (int i = 0; i < _dims->cols; i++)
                    rrefMatrix->_values[leads*_dims->cols + i] *= divider;

                // Column zeroing
                for (int i = 0; i < _dims->rows; i++)
                    if ((i != leads) && ((*rrefMatrix)(i, c) != 0)) // Careful not to zero my current beloved row
                    {
                        divider = (*rrefMatrix)(i, c) / (*rrefMatrix)(leads, c);
                        for (int j = 0; j < _dims->cols; j++)
                            rrefMatrix->_values[i*_dims->cols + j] = (*rrefMatrix)(i, j) - (divider*(*rrefMatrix)(leads, j));
                    }

                leads++;
            }

        }
    }
    return *rrefMatrix;
}

// Returns index (single-dimension index) of the largest number in the matrix.
int Matrix::argmax() const
{

}


// Operators
float Matrix::operator()(int row, int col) const
{
    return _values[row*_dims->cols + col];
}
