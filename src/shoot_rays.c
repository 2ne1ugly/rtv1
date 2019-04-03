/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:31:14 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 21:51:33 by mchi             ###   ########.fr       */
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

t_intersect	*check_intersect(t_ray *ray, t_obj *obj)
{
	t_obj		*curr;
	t_intersect *point;

	point = malloc(sizeof(t_intersect));
	curr = obj;
	while (curr != NULL)
	{
		if (curr->ray_to_obj(ray, curr->obj, point) != 0)
			return (point);
		curr = curr->next;
	}
	free(point);
	return (NULL);
}

void		shoot_rays(t_app *app)
{
	int			i;
	int			j;
	t_ray		ray;
	t_intersect	*point;

	i = 0;
	while (i < app->height)
	{
		j = 0;
		while (j < app->width)
		{
			ray = app->screen_ray[i][j];
			point = check_intersect(&ray, app->scene.objects);
			if (point != NULL)
			{
				img_pixel_put(app, j, i, 0x00FF00);
				free(point);
			}
			else
				img_pixel_put(app, j, i, 0x888888);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(app->mlx_handle,
		app->wnd_handle, app->img.ptr, 0, 0);
}
