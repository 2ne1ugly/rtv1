/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:31:14 by mchi              #+#    #+#             */
/*   Updated: 2019/04/11 17:23:11 by mchi             ###   ########.fr       */
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

void		*shoot_rays(void *arg)
{
	int			i;
	int			j;
	t_ray		ray;
	t_args		*args;
	t_app		*app;

	args = arg;
	app = args->app;
	i = 0;
	while (i < app->height)
	{
		j = args->index;
		while (j < app->width)
		{
			ray = app->screen_ray[i][j];
			img_pixel_put(app, j, i, shoot_view(&ray, app->scene.objects,
				app->scene.lights));
			j += args->threads;
		}
		i++;
	}
	free(arg);
	return (0);
}
