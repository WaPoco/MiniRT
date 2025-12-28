/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:17:16 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/28 18:18:06 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

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
