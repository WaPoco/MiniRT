/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:56 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/30 18:46:44 by vpogorel         ###   ########.fr       */
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

	size = 4;
	result = malloc(size * sizeof(double *));
	if (!result)
		return (NULL);
	i[0] = -1;
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
			return (free_nxn_matrix(transposed, 4), NULL);
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
	int		i[2];
	double	**inv_t;
	double	**inverse;
	double	**inv;

	size = 4;
	i[0] = -1;
	i[1] = -1;
	inv = malloc(size * sizeof(double *));
	if (!inv)
		return (NULL);
	while (++i[0] < size)
	{
		inv[i[0]] = malloc(size * sizeof(double));
		if (!inv[i[0]])
			return (free_nxn_matrix(inv, size), NULL);
		i[1] = -1;
		while (++i[1] < size)
			inv[i[0]][i[1]] = pow(-1, i[1] + i[0])
				* det_adj(i[0], i[1], matrix);
	}
	inv_t = transpose(inv, size);
	inverse = scalar_product_matrix(inv_t, 1.0 / det_4x4(matrix));
	return (free_nxn_matrix(inv, size), free_nxn_matrix(inv_t, size), inverse);
}

double	**scalar_product_matrix(double **matrix, double scalar)
{
	int		size;
	double	**result;
	int		i;
	int		j;

	size = 4;
	result = malloc(size * sizeof(double *));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		result[i] = malloc(size * sizeof(double));
		if (!result[i])
			return (free_nxn_matrix(result, 4), NULL);
		j = -1;
		while (++j < size)
			result[i][j] = matrix[i][j] * scalar;
	}
	return (result);
}
