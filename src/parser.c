/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:44:47 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/31 11:50:30 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

int	parse_scene(const char *filename, t_world *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	init_scene(scene);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
			return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_scene(scene));
}

int	parse_line(char *line, t_world *scene)
{
	char	**tokens;
	//	*tmp;

	//tmp = ft_strtrim(line, " \t\n");
	//free(line);
	//line = tmp;
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	if (!tokens[0])
		return (free_split(tokens), 1);
	if (!ft_strncmp(tokens[0], "A", 1))
		return (parse_ambient(tokens, scene), free_split(tokens), 1);
	else if (!ft_strncmp(tokens[0], "C", 1))
		return (parse_camera(tokens, scene), free_split(tokens), 1);
	else if (!ft_strncmp(tokens[0], "L", 1))
		return (parse_light(tokens, scene), free_split(tokens), 1);
	else if (!ft_strncmp(tokens[0], "sp", 2))
		return (parse_sphere(tokens, scene), free_split(tokens), 1);
	else if (!ft_strncmp(tokens[0], "pl", 2))
		return (parse_plane(tokens, scene), free_split(tokens), 1);
	else if (!ft_strncmp(tokens[0], "cy", 2))
		return (parse_cylinder(tokens, scene), free_split(tokens), 1);
	else
		return (free_split(tokens), 0);
}

int	parse_color(char *str, t_color *out)
{
	int		rgb[3];
	char	**components;
	int		i;

	components = ft_split(str, ',');
	if (!components)
		return (0);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
		return (free_split(components), 0);
	i = 0;
	while (i < 3)
	{
		rgb[i] = atoi(components[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_split(components), 0);
		i++;
	}
	out->r = (double)rgb[0] / 255.0;
	out->g = (double)rgb[1] / 255.0;
	out->b = (double)rgb[2] / 255.0;
	free_split(components);
	return (1);
}
