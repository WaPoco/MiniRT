/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:24:50 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/30 18:35:03 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"
#include "../libft/libft.h"

int	parse_tuple(const char *s, t_tuple *out)
{
	char	**parts;
	double	x;
	double	y;
	double	z;

	if (!s || !out)
		return (0);
	parts = ft_split(s, ',');
	if (!parts)
		return (0);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_split(parts);
		return (0);
	}
	if (!parse_double(parts[0], &x)
		|| !parse_double(parts[1], &y)
		|| !parse_double(parts[2], &z))
		return (free_split(parts), 0);
	out->x = x;
	out->y = y;
	out->z = z;
	out->type = 0;
	free_split(parts);
	return (1);
}
