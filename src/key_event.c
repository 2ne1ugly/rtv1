/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:04:51 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/13 12:12:59 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int	key_event(int keycode, void *ptr)
{
	t_app	*app;

	app = ptr;
	if (keycode == 53)
		exit(0);
	if (keycode == 0)
		app->cam.pos.x -= .5;
	if (keycode == 2)
		app->cam.pos.x += .5;
	if (keycode == 1)
		app->cam.pos.z -= .5;
	if (keycode == 13)
		app->cam.pos.z += .5;
	run_threads(app);
	return (0);
}
