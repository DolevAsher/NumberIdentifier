#include "Activation.h"

#include <algorithm>
#include <cmath>

Matrix& Activation::relu(const Matrix& m)
{
    auto newMat = new Matrix(m.get_rows(), m.get_cols());
    float temp = 0;
    for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
        (*newMat)[i] = std::max(m[i], 0.0f);
    return *newMat;
}

Matrix& softmax(const Matrix& m)
{
    auto newMat = new Matrix(m.get_rows(), m.get_cols());
    float sum = 0.0f;
    for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
        sum += std::exp(m[i]);
    for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
        (*newMat)[i] = std::exp(m[i]) / sum;
    return *newMat;
}