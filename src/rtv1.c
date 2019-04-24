/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:13:29 by mchi              #+#    #+#             */
/*   Updated: 2019/04/24 12:01:14 by zfaria           ###   ########.fr       */
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
	add_scene_sphere(app, &(t_vec){0, 0, 0, 1}, .25, 0xFF0000);
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
