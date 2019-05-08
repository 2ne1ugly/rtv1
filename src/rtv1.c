/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 03:13:29 by mchi              #+#    #+#             */
/*   Updated: 2019/05/08 12:26:26 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

int		main(int argc, char **argv)
{
	t_app		*app;

	if (!init_app(&app))
		return (0);
	app->scene.objects = 0;
	app->scene.lights = 0;
	if (argc == 1)
		parse_config(app, "config/config.rtv");
	else
		parse_config(app, argv[1]);
	camera_update(&app->cam);
	run_threads(app);
	mlx_loop(app->mlx_handle);
	return (0);
}
