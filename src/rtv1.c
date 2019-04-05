/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:13:29 by mchi              #+#    #+#             */
/*   Updated: 2019/04/04 22:19:22 by mchi             ###   ########.fr       */
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

void	add_scene_sphere(t_app *app, t_vec *pos, double radius, int color)
{
	t_obj		*new;
	t_sphere	*sphere;

	new = add_scene_obj(app);
	sphere = malloc(sizeof(t_sphere));
	sphere->pos = *pos;
	sphere->radius = radius;
	new->obj = sphere;
	new->color = color;
	new->ray_to_obj = ray_to_sphere;
}

void	add_scene_plane(t_app *app, t_vec *pos, t_vec *rot, int color)
{
	t_obj		*new;
	t_plane		*plane;

	new = add_scene_obj(app);
	plane = malloc(sizeof(t_plane));
	plane->pos = *pos;
	new->color = color;
	plane->normal = *rot;
	plane->rot = *rot;
	new->obj = plane;
	new->ray_to_obj = ray_to_plane;
}

void	add_scene_cylinder(t_app *app, t_vec *pos, t_vec *rot, int color)
{
	t_obj	*new;
	t_cyl	*cyl;

	new = add_scene_obj(app);
	new->color = color;
	new->ray_to_obj = ray_to_cylinder;
	cyl = malloc(sizeof(t_cyl));
	cyl->pos = *pos;
	cyl->radius = .25;
	cyl->rot = *rot;
	cyl->dir = vec_norm(rot);
	new->obj = cyl;
}

void	add_scene_cone(t_app *app, t_vec *pos, t_vec *rot, double alpha, int color)
{
	t_obj	*new;
	t_cone	*cone;

	new = add_scene_obj(app);
	new->color = color;
	new->ray_to_obj = ray_to_cone;
	cone = malloc(sizeof(t_cone));
	cone->pos = *pos;
	cone->alpha = alpha;
	cone->c2a = cos(alpha) * cos(alpha);
	cone->s2a = sin(alpha) * sin(alpha);
	cone->rot = *rot;
	cone->dir = *rot;
	new->obj = cone;
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
	add_scene_plane(app, &(t_vec){0, -2, 0, 1}, &(t_vec){0, 1, 0, 1}, 0xA0A0A0);
	add_scene_plane(app, &(t_vec){0, 2, 0, 1}, &(t_vec){0, -1, 0, 1}, 0x505050);
	add_scene_plane(app, &(t_vec){0, 0, 5, 1}, &(t_vec){0, 0, -1, 1}, 0x0000FF);
	add_scene_sphere(app, &(t_vec){0, -1.5, 0, 1}, .25, 0xFF0000);
	add_scene_sphere(app, &(t_vec){2, -2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){2, 2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){2, -2, 2, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){2, 2, 2, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, -2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, 2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, -2, 2, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, 2, 2, 1}, .5, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){2, 0, 0, 1}, &(t_vec){0, 1, 0, 1}, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){-2, 0, 0, 1}, &(t_vec){0, 1, 0, 1}, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){2, 0, 2, 1}, &(t_vec){0, 1, 0, 1}, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){-2, 0, 2, 1}, &(t_vec){0, 1, 0, 1}, 0xCCCCCC);
	add_scene_cone(app, &(t_vec){0, 0, 4, 1}, &(t_vec){0, 1, 0, 0}, PI / 12, 0xFFFF00);
	add_scene_cone(app, &(t_vec){-4, 0, 2, 1}, &(t_vec){0, 1, 0, 0}, PI / 12, 0xFFFF00);
	add_scene_cone(app, &(t_vec){4, 0, 2, 1}, &(t_vec){0, 1, 0, 0}, PI / 12, 0xFFFF00);

	app->scene.lights = malloc(sizeof(t_light));
	light = app->scene.lights;
	light->pos = (t_vec){3, 1.5, -1, 1};
	light->next = NULL;
	app->scene.lights->next = malloc(sizeof(t_light));
	light = app->scene.lights->next;
	light->pos = (t_vec){-3, 1.5, -1, 1};
	light->next = NULL;

	run_threads(app);
	mlx_loop(app->mlx_handle);
	return (0);
}
