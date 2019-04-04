/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:31:14 by mchi              #+#    #+#             */
/*   Updated: 2019/04/04 13:44:12 by zfaria           ###   ########.fr       */
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

int			get_color(double dot, double ref, int color)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (ref > 0)
	{
		ref = pow(ref, 3);
		r += ref * 0xFF;
		g += ref * 0xFF;
		b += ref * 0xFF;
		r = MIN(r, 0xFF);	
		g = MIN(g, 0xFF);
		b = MIN(b, 0xFF);
	}
	r *= dot;
	g *= dot;
	b *= dot;
	return ((r << 16) | (g << 8) | (b));
}

int			if_intersects(t_ray *ray, t_obj *obj)
{
	t_obj		*curr;

	curr = obj;
	while (curr != NULL)
	{
		if (curr->ray_to_obj(ray, curr->obj, NULL) != 0)
		{
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

double		check_intersect(t_ray *ray, t_obj *obj, t_light *light)
{
	t_obj		*curr;
	t_vec		point_to_light;
	t_vec		reflection;
	t_ray		new_ray;
	t_obj		*last_obj;

	t_intersect	point;
	t_intersect last;

	point.dist = 9999;
	last_obj = NULL;
	curr = obj;
	while (curr != NULL)
	{
		if (curr->ray_to_obj(ray, curr->obj, &last) != 0)
		{
			if (last.dist < point.dist)
			{
				point = last;
				last_obj = curr;
			}
		}
		curr = curr->next;
	}
	if (point.dist < 9990)
	{
		point_to_light = vec_sub(&light->pos, point.pos);
		point_to_light = vec_norm(&point_to_light);
		new_ray.pos = point.pos;
		new_ray.dir = point_to_light;
		if (if_intersects(&new_ray, obj))
			return (0x000000);
		reflection = vec_sub(&ray->dir, vec_mul(point.normal,
		2 * vec_dot(&ray->dir, &point.normal)));
		reflection = vec_norm(&reflection);
		return (MAX(get_color(
			vec_dot(&point.normal, &point_to_light), 
			vec_dot(&reflection, &point_to_light), last_obj->color), 0));
	}
	return (-1);
}

void		shoot_rays(t_app *app)
{
	int			i;
	int			j;
	t_ray		ray;
	double		color;

	i = 0;
	while (i < app->height)
	{
		j = 0;
		while (j < app->width)
		{
			ray = app->screen_ray[i][j];
			color = check_intersect(&ray, app->scene.objects,
				app->scene.lights);
			if (color == -1)
				img_pixel_put(app, j, i, 0x888888);
			else
				img_pixel_put(app, j, i, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(app->mlx_handle,
		app->wnd_handle, app->img.ptr, 0, 0);
}
