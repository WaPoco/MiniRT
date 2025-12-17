/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:56 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/17 18:19:02 by vpogorel         ###   ########.fr       */
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

void	free_nxn_matrix(double **matrix, int n)
{
	int	i;

	i = 0;
	while (i < n)
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
	int		i[2];
	double	**inv_t;
	double	**inverse;
	double	**inv;

	size = 4;
	i[0] = -1;
	i[1] = -1;
	inv = malloc(size * sizeof(double *));
	if (!inv)
		return (free_4x4_matrix(inv), NULL);
	while (++i[0] < size)
	{
		inv[i[0]] = malloc(size * sizeof(double));
		if (!inv[i[0]])
			return (free_4x4_matrix(inv), NULL);
		i[1] = -1;
		while (++i[1] < size)
			inv[i[0]][i[1]] = pow(-1, i[1] + i[0])
				* det_adj(i[0], i[1], matrix);
	}
	inv_t = transpose(inv, size);
	inverse = scalar_product_matrix(inv_t, 1.0 / det_4x4(matrix));
	return (free(inv), free(inv_t), inverse);
}

double	det_4x4(double **matrix)
{
	double	det;
	int		j;

	det = 0;
	j = 0;
	while (j < 4)
	{
		det += matrix[0][j] * pow(-1, j) * det_adj(0, j, matrix);
		j++;
	}
	return (det);
}

double **allocate_4x4_matrix()
{
	double	**matrix;
	int		i;

	i = 0;
	matrix = (double **)malloc(4 * sizeof(double *));
	while (i < 4)
	{
		matrix[i] = (double *)malloc(4 * sizeof(double));
		if (!matrix[i])
			return (free_nxn_matrix(matrix, 4), NULL);
		i++;
	}
	return (matrix);
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

double	**extract_adj(int i, int j, double **matrix)
{
	int		size;
	double	**adj;
	int		n[4];

	size = 4;
	n[0] = -1;
	n[2] = 0;
	n[3] = 0;
	adj = malloc(size * sizeof(double *));
	if (!adj)
		return (NULL);
	while (++n[0] < size)
	{
		adj[n[0]] = malloc(size * sizeof(double));
		if (!adj[n[0]])
			return (free_nxn_matrix(adj, 3), NULL);
		n[1] = -1;
		while (++n[1] < size)
		{
			if (n[0] != i && n[1] != j)
				if (extract_adj_assign(n, matrix, adj))
					return (adj);
		}
	}
	return (adj);
}

int	extract_adj_assign(int *n, double **matrix, double **adj)
{
	adj[n[2]][n[3]] = matrix[n[0]][n[1]];
	n[3]++;
	if (n[3] == 3)
	{
		n[3] = 0;
		n[2]++;
	}
	if (n[2] == 3 && n[3] == 0)
		return (1);
	return (0);
}

double	det_adj(int i, int j, double **matrix)
{
	double	**adj;
	double	det;

	det = 0;
	i = 0;
	adj = extract_adj(i, j, matrix);
	if (!adj)
		return (0);
	det = adj[0][0] * (adj[1][1] * adj[2][2] - adj[1][2]
			* adj[2][1]) - adj[0][1] * (adj[1][0] * adj[2][2] - adj[1][2]
			* adj[2][0]) + adj[0][2] * (adj[1][0] * adj[2][1] - adj[1][1]
			* adj[2][0]);
	while (i < 3)
		free(adj[i++]);
	free(adj);
	return (det);
}
