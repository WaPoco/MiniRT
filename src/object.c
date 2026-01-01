/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:29:03 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/31 15:43:16 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_object	*object_new(t_obj_type type, void *shape, t_color color)
{
	t_object	*o;

	o = (t_object *)malloc(sizeof(t_object));
	if (!o)
		return (NULL);
	o->type = type;
	o->shape = shape;
	o->mat.color = color;
	o->next = NULL;
	return (o);
}

void	object_add(t_object **lst, t_object *new_obj)
{
	t_object	*cur;

	if (!new_obj)
		return ;
	if (!*lst)
	{
		*lst = new_obj;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new_obj;
}
