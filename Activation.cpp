#include "Activation.h"

#include <algorithm>
#include <cmath>

Matrix& activation::relu(const Matrix& m)
{
    auto newMat = new Matrix(m.get_rows(), m.get_cols());
    for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
        (*newMat)[i] = std::max(m[i], 0.0f);
    return *newMat;
}

Matrix& activation::softmax(const Matrix& m)
{
    auto newMat = new Matrix(m.get_rows(), m.get_cols());
    float sum = 0.0f;
    for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
        sum += std::exp(m[i]);
    for (int i = 0; i < m.get_rows()*m.get_cols(); ++i)
        (*newMat)[i] = std::exp(m[i]) / sum;
    return *newMat;
}