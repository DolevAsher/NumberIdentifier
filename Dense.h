// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense
{
private:
    Matrix* _weights;
    Matrix* _bias;
    ActivationFunction _function;

public:
    Dense(Matrix& weights, Matrix& bias, ActivationFunction function);
    Dense(const Dense& d); // Copy constructor
    ~Dense();

    Matrix& get_weights() const;
    Matrix& get_bias() const;
    ActivationFunction get_activation() const;

    // Applies the layer on the input and returns an output matrix
    Matrix& operator()(const Matrix &m) const;
};









#endif //DENSE_H