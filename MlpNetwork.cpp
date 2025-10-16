#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[])
{
    for (int i = 0; i < MLP_SIZE; i++)
    {
        if (weights[i].get_cols() != weights_dims[i].cols ||
            weights[i].get_rows() != weights_dims[i].rows)
            throw std::invalid_argument("weights and weights_dims"
                                        " do not match");
        if (biases[i].get_cols() != bias_dims[i].cols ||
            biases[i].get_rows() != bias_dims[i].rows)
            throw std::invalid_argument("biases and bias_dims"
                                        " do not match");
    }
    for (int i = 0; i < MLP_SIZE - 1; i++)
        _dense[i] = new Dense(weights[i], biases[i], activation::relu);
    _dense[MLP_SIZE - 1] = new Dense(weights[3],
        biases[3], activation::softmax);
}

// Applying the matrices
digit& MlpNetwork::operator()(const Matrix& input) const
{
    Matrix output1, output2, output3, output4;
    output1 = (*_dense[0])(input);
    output2 = (*_dense[1])(output1);
    output3 = (*_dense[2])(output2);
    output4 = (*_dense[3])(output3);

    auto dig = new digit();
    dig->value = output4.argmax();
    dig->probability = output4[(int)dig->value];
    return *dig;
}