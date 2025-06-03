// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

// Insert Dense class here...
class Dense
{
private:
    Matrix weights_, bias_;
    ActivationFunction function_;

public:
    Dense(Matrix weights, Matrix bias, ActivationFunction function);
    Dense(Dense &d);
    ~Dense();

    Matrix get_weights() const;
    Matrix get_bias() const;
    ActivationFunction get_function() const;

    Matrix operator()(Matrix &m); // Applies the layer on the input and returns an output matrix
};









#endif //DENSE_H