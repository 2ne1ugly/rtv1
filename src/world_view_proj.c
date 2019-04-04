/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_view_proj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 21:44:02 by mchi              #+#    #+#             */
/*   Updated: 2019/04/04 11:33:30 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

/*
** -z is front, y is up, x is right, right handed system.
*/

void	set_basis(t_cam *cam)
{
	cam->z_axis = vec_mul(cam->dir, -1);
	cam->z_axis = vec_norm(&cam->z_axis);
	cam->x_axis = (t_vec){0.0, 1.0, 0.0, 0.0};
	cam->x_axis = vec_cross(&cam->z_axis, &cam->x_axis);
	cam->y_axis = vec_cross(&cam->x_axis, &cam->z_axis);
}
