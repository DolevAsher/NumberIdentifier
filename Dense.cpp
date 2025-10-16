#include "Activation.h"
#include "Dense.h"
#include "Matrix.h"

// Constructor
Dense::Dense(Matrix& weights, Matrix& bias, ActivationFunction function)
{
    _weights = new Matrix(weights);
    _bias = new Matrix(bias);
    _function = function;
}

// Copy constructor
Dense::Dense(const Dense& d)
{
    _weights = new Matrix(d.get_weights());
    _bias = new Matrix(d.get_bias());
    _function = d._function;
}

// Destructor
Dense::~Dense()
{
    delete _weights;
    delete _bias;
}


// Getters
Matrix& Dense::get_weights() const
{
    return *_weights;
}

Matrix& Dense::get_bias() const
{
    return *_bias;
}

ActivationFunction Dense::get_activation() const
{
    return _function;
}

Matrix& Dense::operator()(const Matrix &m) const
{
    if (_weights->get_cols() != m.get_rows() ||
        _bias->get_rows() != _weights->get_rows())
        throw std::runtime_error("Sizes differences in Layer Operation.");
    return _function((*_weights)*(m) + (*_bias));
}
