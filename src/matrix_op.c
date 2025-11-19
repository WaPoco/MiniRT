#include "../Include/miniRT.h"

t_tuple    matrix_mult(double **matrix, t_tuple point)
{
    // To be implemented
    double result[4] = {0, 0, 0, 0};
    int i = 0;
    // calculate matrix multiplication with tuple type here
    while (i < 3)
    {
        result[i] = matrix[i][0] * point.x +
                    matrix[i][1] * point.y +
                    matrix[i][2] * point.z;
        i++;
    }
    return (create_tuple(result[0], result[1], result[2])); 
}

double **inverse_matrix(double **matrix)
{
    // implement matrix inversion, but recursively for 4x4 matrices
    return NULL;
}