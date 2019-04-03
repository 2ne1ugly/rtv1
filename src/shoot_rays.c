/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:31:14 by mchi              #+#    #+#             */
/*   Updated: 2019/04/03 14:59:28 by zfaria           ###   ########.fr       */
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
	min = vec_sub(&min, vec_mul(app->cam.x_axis, step));
	min = vec_sub(&min, vec_mul(app->cam.y_axis, step * app->aspect));
	step /= app->height / 2;
	i = -1;
	while (++i < app->height)
	{
		j = -1;
		while (++j < app->width)
		{
			ray.dir = vec_add(&min, vec_mul(app->cam.y_axis, i * step));
			ray.dir = vec_add(&ray.dir, vec_mul(app->cam.x_axis,
			j * step * app->aspect));
			ray.dir = vec_norm(&ray.dir);
			app->screen_ray[i][j] = ray;
		}
	}
}

double		check_intersect(t_ray *ray, t_obj *obj, t_light *light)
{
	t_obj		*curr;
	t_intersect *point;
	t_vec		point_to_light;
	t_vec		reflection;

	point = malloc(sizeof(t_intersect));
	curr = obj;
	while (curr != NULL)
	{
		if (curr->ray_to_obj(ray, curr->obj, point) != 0)
		{
			point_to_light = vec_sub(&light->pos, point->pos);
			point_to_light = vec_norm(&point_to_light);
			reflection = vec_sub(&ray->dir, vec_mul(point->normal, 2 * vec_dot(&ray->dir, &point->normal)));
			reflection = vec_norm(&reflection);
			free(point);
			return (MAX(vec_dot(&reflection, &point_to_light), 0));
		}
		curr = curr->next;
	}
	free(point);
	return (-1);
}

void		shoot_rays(t_app *app)
{
	int			i;
	int			j;
	t_ray		ray;
	double		color;
	int			val;

	i = 0;
	while (i < app->height)
	{
		j = 0;
		while (j < app->width)
		{
			ray = app->screen_ray[i][j];
			color = check_intersect(&ray, app->scene.objects, app->scene.lights);
			if (color == -1)
			{
				img_pixel_put(app, j, i, 0x888888);
			}
			else
			{
				val = color * 0xFF;
				img_pixel_put(app, j, i, val << 8);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(app->mlx_handle,
		app->wnd_handle, app->img.ptr, 0, 0);
}
