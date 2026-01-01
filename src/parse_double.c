/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:06:22 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/30 18:27:03 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"
#include "../libft/libft.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '\n' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	parse_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	parse_int_part(const char *s, int *i, double *res)
{
	int	found;

	found = 0;
	while (ft_isdigit(s[*i]))
	{
		*res = (*res) * 10.0 + (s[*i] - '0');
		(*i)++;
		found = 1;
	}
	return (found);
}

int	parse_frac_part(const char *s, int *i, double *res)
{
	double	div;
	int		found;

	if (s[*i] != '.')
		return (1);
	div = 10.0;
	found = 0;
	(*i)++;
	while (ft_isdigit(s[*i]))
	{
		*res += (s[*i] - '0') / div;
		div *= 10.0;
		(*i)++;
		found = 1;
	}
	if (!found)
		return (0);
	return (1);
}

int	parse_double(const char *s, double *out)
{
	int		i;
	int		sign;
	double	val;

	if (!s || !out)
		return (0);
	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	sign = parse_sign(s, &i);
	val = 0.0;
	if (!parse_int_part(s, &i, &val))
		return (0);
	if (!parse_frac_part(s, &i, &val))
		return (0);
	while (s[i] && is_space(s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	*out = val * sign;
	return (1);
}
