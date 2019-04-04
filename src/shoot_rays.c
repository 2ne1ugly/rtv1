/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:31:14 by mchi              #+#    #+#             */
/*   Updated: 2019/04/04 15:42:46 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	ray is stored in y and x order
*/

void		set_rays(t_app *app)
{
	int			i;
	int			j;
	t_ray		ray;
	t_vec		min;
	double		step;

	ray.pos = app->cam.pos;
	min = vec_mul(app->cam.dir, app->cam.near);
	step = vec_abs(&min) * tan(app->cam.fov / 2.0);
	min = vec_add(&min, vec_mul(app->cam.y_axis, step));
	min = vec_sub(&min, vec_mul(app->cam.x_axis, step * app->aspect));
	step /= app->height / 2.0;
	i = -1;
	while (++i < app->height)
	{
		j = -1;
		while (++j < app->width)
		{
			ray.dir = vec_sub(&min, vec_mul(app->cam.y_axis, i * step));
			ray.dir = vec_add(&ray.dir, vec_mul(app->cam.x_axis,
			j * step * app->aspect));
			ray.dir = vec_norm(&ray.dir);
			app->screen_ray[i][j] = ray;
		}
	}
}

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
		spec = pow(spec, 3);
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
	ray_to_light.pos = vec_add(from, vec_mul(ray_to_light.dir, 0.01));
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

double		find_spec(t_ray *incident, t_intersect *itrsct,
	t_light *lights, t_obj *obj)
{
	t_vec	reflect;
	t_ray	to_light;
	double	spec;
	double	val;

	spec = 0;
	while (lights != NULL)
	{
		to_light.pos = itrsct->pos;
		to_light.dir = vec_sub(&lights->pos, itrsct->pos);
		to_light.dir = vec_norm(&to_light.dir);
		if (!is_blocking_light(&to_light.pos, obj, &lights->pos))
		{
			reflect = vec_rflct(&incident->dir, &itrsct->normal);
			val = vec_dot(&reflect, &to_light.dir);
			if (val > 0)
				spec += pow(val, 3);
		}
		lights = lights->next;
	}
	return (spec);
}

double		find_diff(t_intersect *itrsct,
	t_light *lights, t_obj *obj)
{
	t_ray	to_light;
	double	diffuse;
	double	val;

	diffuse = 0;
	while (lights != NULL)
	{
		to_light.pos = itrsct->pos;
		to_light.dir = vec_sub(&lights->pos, itrsct->pos);
		to_light.dir = vec_norm(&to_light.dir);
		if (!is_blocking_light(&to_light.pos, obj, &lights->pos))
		{
			val = vec_dot(&itrsct->normal, &to_light.dir);
			if (val > 0)
				diffuse += val;
		}
		lights = lights->next;
	}
	return (diffuse);
}

int			shoot_view(t_ray *ray, t_obj *obj, t_light *lights)
{
	t_intersect	itrsct;
	double		spec;
	double		diff;

	itrsct = find_first_intersect(ray, obj);
	if (itrsct.obj == NULL)
		return (0x888888);
	spec = find_spec(ray, &itrsct, lights, obj);
	diff = find_diff(&itrsct, lights, obj);
	return (get_color(diff, spec, itrsct.obj->color));
}

void		shoot_rays(t_app *app)
{
	int			i;
	int			j;
	t_ray		ray;

	i = 0;
	while (i < app->height)
	{
		j = 0;
		while (j < app->width)
		{
			ray = app->screen_ray[i][j];
			img_pixel_put(app, j, i, shoot_view(&ray, app->scene.objects,
				app->scene.lights));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(app->mlx_handle,
		app->wnd_handle, app->img.ptr, 0, 0);
}
