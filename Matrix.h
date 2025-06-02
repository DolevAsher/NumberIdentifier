// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H



// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};


// Matrix class
class Matrix
{
private:
    matrix_dims dims; // Dimensions struct
    float* values; // A pointer to the array of the values of the matrix

public:
    // Constructors
    Matrix(); // Default constructor
    Matrix (int rows, int cols);
    Matrix (int rows, int cols, float* values);
    // Distructor
    ~Matrix();

    matrix_dims get_dimensions();

    float* get_values();
};



#endif //MATRIX_H