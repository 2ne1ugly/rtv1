/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:04:51 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/24 12:03:02 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	camera_update(t_cam *cam)
{
	t_mat rot_mat;

	rot_mat = rotation_mat(cam->rot.x, cam->rot.y, cam->rot.z);
	vec_transform(&cam->dir, &(t_vec){0.0, 0.0, 1.0, 0.0}, &rot_mat);
}

int		key_event(int keycode, void *ptr)
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
	if (keycode == 124)
		app->cam.rot.y -= .05;
	if (keycode == 123)
		app->cam.rot.y += .05;
	run_threads(app);
	return (0);
}
