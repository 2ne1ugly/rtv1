/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:33:01 by mchi              #+#    #+#             */
/*   Updated: 2019/04/24 11:52:36 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

int			event_close(void *ptr)
{
	(void)ptr;
	exit(0);
	return (1);
}

void		hook_functions(t_app *app)
{
	mlx_hook(app->wnd_handle, 2, 0, key_event, app);
	mlx_loop_hook(app->mlx_handle, app_looper, app);
	mlx_hook(app->wnd_handle, 17, 1L << 17, event_close, app);
}

void		init_img(t_app *app)
{
	app->img.ptr =
		mlx_new_image(app->mlx_handle, app->width, app->height);
	app->img.data_addr =
		mlx_get_data_addr(app->img.ptr, &app->img.bpp,
			&app->img.sl, &app->img.endian);
	app->img.bpp /= 8;
}

void		init_screen_ray(t_app *app)
{
	int i;

	app->screen_ray = malloc(sizeof(t_ray *) * app->height);
	i = 0;
	while (i < app->height)
	{
		app->screen_ray[i] = malloc(sizeof(t_ray) * app->width);
		i++;
	}
}

int			init_app(t_app **app)
{
	*app = malloc(sizeof(t_app));
	if (*app == NULL)
		return (0);
	(*app)->mlx_handle = mlx_init();
	if ((*app)->mlx_handle == NULL)
		return (0);
	(*app)->width = 900;
	(*app)->height = 900;
	(*app)->aspect = (*app)->width / (*app)->height;
	(*app)->wnd_handle =
		mlx_new_window((*app)->mlx_handle,
			(*app)->width, (*app)->height, "wfew");
	if ((*app)->wnd_handle == NULL)
		return (0);
	init_img(*app);
	init_screen_ray(*app);
	(*app)->cam.rot = (t_vec){0, 0, 0, 0};
	(*app)->cam.pos = (t_vec){0, 0, -5, 1};
	(*app)->cam.fov = PI / 2.5;
	(*app)->cam.near = 0.1;
	hook_functions(*app);
	return (1);
}
