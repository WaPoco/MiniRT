/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:05:02 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/28 18:16:45 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

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

double	**allocate_4x4_matrix(void)
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
