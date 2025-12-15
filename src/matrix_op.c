/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:56 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/15 21:04:27 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_tuple	matrix_mult(double **matrix, t_tuple point)
{
	double	result[4];
	int		i;

	i = 0;
	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	result[3] = 0;
	while (i < 4)
	{
		result[i] = matrix[i][0] * point.x + matrix[i][1] * point.y
			+ matrix[i][2] * point.z + matrix[i][3] * point.type;
		i++;
	}
	return (create_tuple(result[0], result[1], result[2]));
}

double	**matrix_mult_4x4(double **a, double **b)
{
	int		size;
	int		i[3];
	double	**result;

	result = malloc(size * sizeof(double *));
	if (!result)
		return (NULL);
	i[0] = -1;
	size = 4;
	while (++i[0] < size)
	{
		result[i[0]] = malloc(size * sizeof(double));
		if (!result[i[0]])
			return (NULL);
		i[1] = -1;
		while (++i[1] < size)
		{
			result[i[0]][i[1]] = 0;
			i[2] = -1;
			while (++i[2] < size)
				result[i[0]][i[1]] += a[i[0]][i[2]] * b[i[2]][i[1]];
		}
	}
	return (result);
}

void	free_4x4_matrix(double **matrix)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	if (matrix)
		free(matrix);
}

double	**transpose(double **matrix, int size)
{
	int		i;
	int		j;
	double	**transposed;

	transposed = malloc(size * sizeof(double *));
	if (!transposed)
		return (NULL);
	i = 0;
	while (i < size)
	{
		transposed[i] = malloc(size * sizeof(double));
		if (!transposed[i])
			return (free_4x4_matrix(transposed), NULL);
		j = 0;
		while (j < size)
		{
			transposed[i][j] = matrix[j][i];
			j++;
		}
		i++;
	}
	return (transposed);
}

double	**inverse_matrix(double **matrix)
{
	int		size;
	int		i;
	int		j;
	double	**inv_t;
	double	**inverse;
	double	*inv;

	size = 4;
	i = 0;
	inv = malloc(size * sizeof(double *));
	if (!inv)
		return (NULL);
	while (i < size)
	{
		inv[i] = malloc(size * sizeof(double));
		if (!inv[i])
			return (NULL);
		j = 0;
		while (j < size)
        {
			inv[i][j] = pow(-1, j + i) * det_adj(i, j, matrix);
            j++;
        }
        i++;
    }
    // transpose inv and divide by determinant
    inv_t = transpose(inv, size);
    inverse = scalar_product_matrix(inv_t, 1.0 / det_4x4(matrix));
    free(inv);
    free(inv_t);
    // print the inverse matrix for debugging
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

double **allocate_4x4_matrix()
{
    double **matrix = (double **)malloc(4 * sizeof(double *));
    for (int i = 0; i < 4; i++)
        matrix[i] = (double *)malloc(4 * sizeof(double));
    return matrix;
}

// i need a function that scales a matrix by a scalar in x and y direction and z direction
/*void scaling(t_tuple *P, double x, double y, double z)
{
    P.x = x * P.x;
    P.y = y * P.y;
    P.z = z * P.z;
}*/
 
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
    int size = 4;
    int t = 0;
    int u = 0;
    int k = 0;
    int p = 0;
    double **adj = malloc(size * sizeof(double *));
    while (t<size)
    {
        adj[t] = malloc(size * sizeof(double));
        u = 0;
        while (u<size)
        {
            if (t != i && u != j)
            {
                adj[k][p] = matrix[t][u];
                p++;
                if (p == 3)
                {
                    p%=3;
                    k++;
                }
                if (k == 3 && p == 0)
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
    // print adj matrix
    // int k = 0;
    /*
    printf( "Adjoint matrix for element (%d, %d):\n", i, j);
    while (k<3)
    {
        int l = 0;
        while (l<3)
        {
            printf("%f ", adj[k][l]);
            l++;
        }
        printf("\n");
        k++;
    }*/
    double det = 0;
    det = adj[0][0] * (adj[1][1] * adj[2][2] - adj[1][2] * adj[2][1]) -
          adj[0][1] * (adj[1][0] * adj[2][2] - adj[1][2] * adj[2][0]) +
          adj[0][2] * (adj[1][0] * adj[2][1] - adj[1][1] * adj[2][0]);
    // write the det value for debugging
    //printf("Determinant of adjoint matrix: %f\n", det);
    while (i<3)
    {
        free(adj[i]);
        i++;
    }
    free(adj);
    return (det);
}