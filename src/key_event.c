/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:04:51 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/03 16:00:42 by zfaria           ###   ########.fr       */
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
		app->scene.lights->pos.x -= .5;
	if (keycode == 2)
		app->scene.lights->pos.x += .5;
	if (keycode == 1)
		app->scene.lights->pos.y -= .5;
	if (keycode == 13)
		app->scene.lights->pos.y += .5;
	shoot_rays(app);
	return (0);
}
