/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:13:29 by mchi              #+#    #+#             */
/*   Updated: 2019/04/03 11:50:13 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

int	main(void)
{
	t_app		*app;
	t_sphere	*sphere;
	t_light		*light;

	if (!init_app(&app))
		return (0);
	set_basis(&app->cam);
	set_rays(app);
	app->scene.objects = malloc(sizeof(t_obj));
	app->scene.objects->next = NULL;
	app->scene.objects->ray_to_obj = ray_to_sphere;
	app->scene.objects->obj = malloc(sizeof(t_sphere));
	sphere = app->scene.objects->obj;
	sphere->pos = (t_vec){0, 0, 0, 1};
	sphere->radius = 0.5;

	app->scene.lights = malloc(sizeof(t_light));
	light = app->scene.lights;
	light->pos = (t_vec){2, -2, -2, 1};
	light->next = NULL;
	shoot_rays(app);
	mlx_loop(app->mlx_handle);
	return (0);
}
