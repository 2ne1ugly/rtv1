/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:13:29 by mchi              #+#    #+#             */
/*   Updated: 2019/04/03 15:00:52 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

t_obj	*add_scene_obj(t_app *app)
{
	t_obj *old;
	t_obj *new;

	if (app->scene.objects == NULL)
	{
		app->scene.objects = malloc(sizeof(t_obj));
		app->scene.objects->next = NULL;
		return (app->scene.objects);
	}
	new = malloc(sizeof(t_obj));
	old = app->scene.objects;
	new->next = old;
	app->scene.objects = new;
	return (new);
}

void	add_scene_sphere(t_app *app, t_vec *pos, t_vec *rot, double radius)
{
	t_obj		*new;
	t_sphere	*sphere;

	new = add_scene_obj(app);
	sphere = malloc(sizeof(t_sphere));
	sphere->pos = *pos;
	sphere->radius = radius;
	sphere->rot = *rot;
	new->obj = sphere;
	new->ray_to_obj = ray_to_sphere;
}

int	main(void)
{
	t_app		*app;
	//t_sphere	*sphere;
	t_light		*light;

	if (!init_app(&app))
		return (0);
	set_basis(&app->cam);
	set_rays(app);
	app->scene.objects = 0;
	/*app->scene.objects = malloc(sizeof(t_obj));
	app->scene.objects->next = NULL;
	app->scene.objects->ray_to_obj = ray_to_sphere;
	app->scene.objects->obj = malloc(sizeof(t_sphere));
	sphere = app->scene.objects->obj;
	sphere->pos = (t_vec){0, 0, 0, 1};
	sphere->radius = 0.5;*/
	add_scene_sphere(app, &(t_vec){-1, 0, 2, 1}, &(t_vec){0, 0, 0, 1}, .5);
	add_scene_sphere(app, &(t_vec){1, 0, 0, 1}, &(t_vec){0, 0, 0, 1}, .5);
	add_scene_sphere(app, &(t_vec){0, 1, 0, 1}, &(t_vec){0, 0, 0, 1}, .5);
	add_scene_sphere(app, &(t_vec){0, -1, 0, 1}, &(t_vec){0, 0, 0, 1}, .5);
	add_scene_sphere(app, &(t_vec){-2, 0, 0, 1}, &(t_vec){0, 0, 0, 1}, .5);

	app->scene.lights = malloc(sizeof(t_light));
	light = app->scene.lights;
	light->pos = (t_vec){2, -2, -2, 1};
	light->next = NULL;
	shoot_rays(app);
	mlx_loop(app->mlx_handle);
	return (0);
}
