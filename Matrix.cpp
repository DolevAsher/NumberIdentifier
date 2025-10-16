#include "Matrix.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>

#define EPSILON_RREF 0.000001

// Constructor
Matrix::Matrix(int row, int col)
{
    if (row < 0 || col < 0)
        throw std::invalid_argument("Invalid dims size.");
    _dims = new matrix_dims();
    _dims->rows = row;
    _dims->cols = col;
    _values = new float[row * col];
    for (int i = 0; i < row * col; i++)
        _values[i] = 0;
}

// Void constructor
Matrix::Matrix()
{
    _dims = new matrix_dims();
    _dims->cols = 1;
    _dims->rows = 1;
    _values = new float[1*1];
    _values[0] = 0;
}

// Copy constructor
Matrix::Matrix(const Matrix& m)
{
    _dims = new matrix_dims();
    _dims->cols = m._dims->cols;
    _dims->rows = m._dims->rows;
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
    _dims->rows = _dims->cols*_dims->rows;
    _dims->cols = 1;
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
        throw std::runtime_error("Matrices in different dimensions.");

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
Matrix Matrix::rref() const
{
    auto rrefMatrix = Matrix(*this);

    // Counter of lead values (current row we're working on)
    int leads = 0;

    // Iterate through each column
    for (int c = 0; c < _dims->cols && leads < _dims->rows; c++)
    {
        // Look for a pivot in the current column,
        // starting from the current lead row
        for (int r = leads; r < _dims->rows; r++)
        {
            // Finding the first non-zero value of the current column
            if (std::abs(rrefMatrix(r, c)) > EPSILON_RREF)
            {

                // Swapping the whole row to the right position (leads row)
                if (r != leads)
                {
                    for (int i = 0; i < _dims->cols; i++)
                        std::swap(rrefMatrix(r, i),
                            rrefMatrix(leads, i));
                }

                // Dividing the row by the pivot value to make it 1
                float pivotValue = rrefMatrix(leads, c);
                for (int i = 0; i < _dims->cols; i++)
                    rrefMatrix(leads, i) /= pivotValue;

                // Column zeroing - eliminate all other entries in this column
                for (int i = 0; i < _dims->rows; i++)
                {
                    // Skip the current pivot row
                    if (i != leads && std::abs(rrefMatrix(i, c))
                        > EPSILON_RREF)
                    {
                        float multiplier = rrefMatrix(i, c);
                        for (int j = 0; j < _dims->cols; j++)
                            rrefMatrix(i, j) -= multiplier *
                                rrefMatrix(leads, j);
                    }
                }

                // Move to the next row for the next pivot
                leads++;
                break; // Break out of the row search loop
            }
        }
    }
    return rrefMatrix;
}

// Returns index (single-dimension index) of the largest number in the matrix.
int Matrix::argmax() const
{
    float max = (*this)[0];
    int index = 0;
    for (int i = 0; i < _dims->rows*_dims->cols; i++)
        if ((*this)[i] > max) // Could have used _values[i]
        {
            max = (*this)[i];
            index = i;
        }
    return index;
}

// Returns the sum of all the elements in the matrix
float Matrix::sum() const
{
    float sum = 0;
    for (int i = 0; i < _dims->rows*_dims->cols; i++)
        sum += _values[i];
    return sum;
}

// Operators
Matrix& Matrix::operator+=(const Matrix& m)
{
    if (_dims->cols != m._dims->cols || _dims->rows != m._dims->rows)
        throw std::runtime_error("Matrices in different dimensions.");
    for (int i = 0; i < _dims->rows*_dims->cols; i++)
        _values[i] += m._values[i];
    return *this;
}

Matrix& Matrix::operator+(const Matrix& m) const
{
    if (_dims->cols != m._dims->cols || _dims->rows != m._dims->rows)
        throw std::runtime_error("Matrices in different dimensions.");
    auto newMat = new Matrix(*this);
    return *newMat+=m;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    _values = new float[m._dims->rows*m._dims->cols];
    _dims->cols = m._dims->cols;
    _dims->rows = m._dims->rows;
    for (int i = 0; i < _dims->rows*_dims->cols; i++)
        _values[i] = m._values[i];
    return *this;
}

Matrix& Matrix::operator*(const Matrix& m) const
{
    if (_dims->cols != m._dims->rows)
        throw std::runtime_error("Matrices dimensions"
                                 " do not fit for multiplication.");
    auto newMat = new Matrix(_dims->rows, m._dims->cols);
    float sum = 0;
    try
    {
        for (int r = 0; r < _dims->rows; r++)
            for (int c = 0; c < m._dims->cols; c++)
            {
                for (int k = 0; k < _dims->cols; k++)
                    sum += _values[r*_dims->cols + k] *
                        m._values[k*m._dims->cols + c];
                newMat->_values[r*newMat->_dims->cols + c] = sum;
                sum = 0;
            }
    }
    catch (...)
    {
        throw;
    }
    return *newMat;
}

Matrix Matrix::operator*(float c) const
{
    Matrix newMat(*this);
    for (int i = 0; i < _dims->rows*_dims->cols; i++)
        newMat[i] *= c;
    return newMat;
}

Matrix operator*(int scalar,const Matrix& m)
{
    Matrix newMat(m);
    for (int i = 0; i < m.get_rows()*m.get_cols(); i++)
        newMat[i] *= scalar;
    return newMat;
}

float Matrix::operator()(int row, int col) const
{
    if (row >= _dims->rows || col >= _dims->cols ||
        row < 0 || col < 0)
        throw std::runtime_error("Out of bounds.");
    return _values[row*_dims->cols + col];
}

float& Matrix::operator()(int row, int col)
{
    if (row >= _dims->rows || col >= _dims->cols ||
        row < 0 || col < 0)
        throw std::runtime_error("Out of bounds.");
    return _values[row*_dims->cols + col];
}

float Matrix::operator[](int index) const
{
    if (index >= _dims->rows*_dims->cols || index < 0)
        throw std::runtime_error("Index out of bounds.");
    return _values[index];
}

float& Matrix::operator[](int index)
{
    if (index >= _dims->rows*_dims->cols || index < 0)
        throw std::runtime_error("Index out of bounds.");
    return _values[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int r = 0; r < m._dims->rows; r++)
    {
        for (int c = 0; c < m._dims->cols; c++)
        {
            if (m._values[r*m._dims->cols + c] > 0.1)
                os << "**";
            else
                os << "  ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    if (!is)
        throw std::runtime_error("Can't read from stream.");

    // is.seekg (0, is.end);
    // long unsigned int length = is.tellg();
    // is.seekg (0, is.beg);

    // if ((int)length < m._dims->rows * m._dims->cols)
    //     throw std::runtime_error("File is too small.");

    const size_t dataSize = m._dims->rows *
        m._dims->cols * sizeof(float);

    if (!is.read(reinterpret_cast<char*>(m._values), dataSize))
        throw std::runtime_error("Failed to read matrix data.");

    return is;
}
