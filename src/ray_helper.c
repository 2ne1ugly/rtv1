/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:22:58 by mchi              #+#    #+#             */
/*   Updated: 2019/04/11 17:24:15 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_color(double diff, double spec, int color)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (spec > 0)
	{
		spec = pow(spec, 5);
		r += spec * 0xFF;
		g += spec * 0xFF;
		b += spec * 0xFF;
		r = MIN(r, 0xFF);
		g = MIN(g, 0xFF);
		b = MIN(b, 0xFF);
	}
	r *= diff;
	g *= diff;
	b *= diff;
	r = MIN(r, 0xFF);
	g = MIN(g, 0xFF);
	b = MIN(b, 0xFF);
	return ((r << 16) | (g << 8) | (b));
}

int			is_blocking_light(t_vec *from, t_obj *obj, t_vec *to)
{
	t_vec	to_light;
	double	length_to_light;
	t_ray	ray_to_light;
	double	inter_section;

	to_light = vec_sub(to, *from);
	length_to_light = vec_abs(&to_light);
	ray_to_light.dir = vec_norm(&to_light);
	ray_to_light.pos = vec_add(from, vec_mul(ray_to_light.dir, 0.000000001));
	while (obj != NULL)
	{
		inter_section = obj->ray_to_obj(&ray_to_light, obj, NULL);
		if (inter_section != 0 && inter_section < length_to_light)
		{
			return (1);
		}
		obj = obj->next;
	}
	return (0);
}

t_intersect	find_first_intersect(t_ray *ray, t_obj *obj)
{
	t_intersect first_intersect;
	t_intersect current_intersect;

	first_intersect.obj = NULL;
	first_intersect.dist = 2000000;
	while (obj != NULL)
	{
		current_intersect.dist = 2000000;
		if (obj->ray_to_obj(ray, obj, &current_intersect) != 0 &&
			current_intersect.dist < first_intersect.dist)
		{
			first_intersect = current_intersect;
		}
		obj = obj->next;
	}
	return (first_intersect);
}
