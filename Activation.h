// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

typedef Matrix (*ActivationFunction)(Matrix);

namespace Activation
{
    /* The function gets a matrix and returns a new matrix.
     * For each entry in the matrix, it will choose the max value between
     * 0 and the entry's value.
     */
    Matrix& relu(const Matrix& m);

    /* The function gets a matrix and returns a new matrix.
     * The new matrix is a normalized value matrix.
     */
    Matrix& softmax(const Matrix& m);
}









#endif //ACTIVATION_H