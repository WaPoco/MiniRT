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

double		**transpose(double **matrix, int size)
{
    int i, j;
    double **transposed = malloc(size * sizeof(double *));
    i = 0;
    while (i<size)
    {
        transposed[i] = malloc(size * sizeof(double));
        j = 0;
        while (j<size)
        {
            transposed[i][j] = matrix[j][i];
            j++;
        }
        i++;
    }
    return (transposed);    
}
double **inverse_matrix(double **matrix)
{
    int size = 4;
    int i, j;
    double **inv_t;
    double **inverse;
    double **inv = malloc(size * sizeof(double *));
    // implement matrix inversion, but recursively(Laplacescher Entwicklungssatz) for 4x4 matrices
    while (i<size)
    {
        inv[i] = malloc(size * sizeof(double));
        j = 0;
        while (j<size)
        {
            inv[i][j] = pow(-1, j) * det_adj(i,j, matrix);
            j++;
        }
        i++;
    }
    // transpose inv and divide by determinant
    inv_t = transpose(inv, size);
    inverse = scalar_product_matrix(inv_t, 1.0 / det_4x4(matrix));
    free(inv);
    free(inv_t);
    return (inverse);
}
// I need a function to calculate determinante of 4x4 matrix using lapce expansion
double  det_4x4(double **matrix)
{
    double det = 0;
    int j = 0;
    while (j<4)
    {
        det += matrix[0][j] * pow(-1, j) * det_adj(0, j, matrix);
        j++;
    }
    return (det);
}
// i need a function scales a matrix by a scalar
double **scalar_product_matrix(double **matrix, double scalar)
{
    int size = 4;
    int i, j;
    double **result = malloc(size * sizeof(double *));
    i = 0;
    while (i<size)
    {
        result[i] = malloc(size * sizeof(double));
        j = 0;
        while (j<size)
        {
            result[i][j] = matrix[i][j] * scalar;
            j++;
        }
        i++;
    }
    return (result);
}

double **extract_adj(int i, int j, double **matrix)
{
    int size = 3;
    int t = 0;
    int u = 0;
    int k = 0;
    int p = 0;
    double **adj = malloc(size * sizeof(double *));
    while (t<size)
    {
        adj[t] = malloc(size * sizeof(double));
        j = 0;
        while (u<size)
        {
            if (t != i && u != j)
            {
                adj[p][k] = matrix[t][u];
                p++;
                if (p == 3)
                {
                    p%=3;
                    k++;
                }
                if (k == 3)
                    return adj;
            }
            u++;
        }
        t++;
    }
    return (adj);
}

double  det_adj(int i, int j, double **matrix)
{
    double **adj = extract_adj(i, j, matrix);
    double det = 0;
    det = adj[0][0] * (adj[1][1] * adj[2][2] - adj[1][2] * adj[2][1]) -
          adj[0][1] * (adj[1][0] * adj[2][2] - adj[1][2] * adj[2][0]) +
          adj[0][2] * (adj[1][0] * adj[2][1] - adj[1][1] * adj[2][0]);
    while (i<3)
    {
        free(adj[i]);
        i++;
    }
    free(adj);
    return (det);
}