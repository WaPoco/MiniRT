/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:44:36 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/02 16:11:40 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	swap_min(double *a, double *b)
{
	double	tmp;

	if (*a > *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}
