/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:13:29 by mchi              #+#    #+#             */
/*   Updated: 2019/04/24 12:05:32 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

int		main(void)
{
	t_app		*app;
	t_light		*light;

	if (!init_app(&app))
		return (0);
	app->scene.objects = 0;
	add_scene_plane(app, &(t_vec){0, -2, 0, 1}, &(t_vec){0, 0, 0, 1}, 0xA0A0A0);
	add_scene_plane(app, &(t_vec){0, 2, 0, 1}, &(t_vec){PI, 0, 0, 1}, 0x505050);
	add_scene_plane(app, &(t_vec){0, 0, 10, 1}, &(t_vec){-PI / 4, 0, 0, 1}, 0x0000FF);
	add_scene_sphere(app, &(t_vec){0, -1.5, 0, 1}, .25, 0xFF0000);
	add_scene_sphere(app, &(t_vec){2, -2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){2, 2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){2, -2, 2, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){2, 2, 2, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, -2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, 2, 0, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, -2, 2, 1}, .5, 0xCCCCCC);
	add_scene_sphere(app, &(t_vec){-2, 2, 2, 1}, .5, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){2, 0, 0, 1}, &(t_vec){0, 0, 0, 0}, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){-2, 0, 0, 1}, &(t_vec){0, 0, 0, 0}, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){2, 0, 2, 1}, &(t_vec){0, 0, 0, 0}, 0xCCCCCC);
	add_scene_cylinder(app, &(t_vec){-2, 0, 2, 1}, &(t_vec){0, 0, 0, 0}, 0xCCCCCC);
	add_scene_cone(app, &(t_vec){0, 0, 4, 1}, &(t_vec){0, 0, 0, PI / 12}, 0xFFFF00);
	add_scene_cone(app, &(t_vec){-4, 0, 2, 1}, &(t_vec){0, 0, 0, PI / 12}, 0xFFFF00);
	add_scene_cone(app, &(t_vec){4, 0, 2, 1}, &(t_vec){0, 0, 0, PI / 12}, 0xFFFF00);
	app->scene.lights = malloc(sizeof(t_light));
	light = app->scene.lights;
	light->pos = (t_vec){3, 1.5, -1, 1};
	light->next = NULL;
	app->scene.lights->next = malloc(sizeof(t_light));
	light = app->scene.lights->next;
	light->pos = (t_vec){-3, 1.5, -1, 1};
	light->next = NULL;
	camera_update(&app->cam);
	run_threads(app);
	mlx_loop(app->mlx_handle);
	return (0);
}
