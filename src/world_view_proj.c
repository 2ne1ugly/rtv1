/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_view_proj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 21:44:02 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 21:11:49 by mchi             ###   ########.fr       */
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
	cam->x_axis = vec_cross(&cam->x_axis, &cam->z_axis);
	cam->y_axis = vec_cross(&cam->z_axis, &cam->x_axis);
}

/*
t_mat	look_at(t_cam cam)
{
	t_mat	result;
	t_vec	eye;

	eye = calc_position(cam);
	z_axis = vector_normal(assign_vector(-eye.x, -eye.y, -eye.z, 0));
	x_axis = vector_normal(vector_cross(assign_vector(0, 1, 0, 0), z_axis));
	y_axis = vector_cross(z_axis, x_axis);
	assign_vector_to_matrix(&result, &x_axis, 0);
	assign_vector_to_matrix(&result, &y_axis, 1);
	assign_vector_to_matrix(&result, &z_axis, 2);
	result.val[3][0] = -vector_dot(&x_axis, &eye);
	result.val[3][1] = -vector_dot(&y_axis, &eye);
	result.val[3][2] = -vector_dot(&z_axis, &eye);
	result.val[0][3] = 0;
	result.val[1][3] = 0;
	result.val[2][3] = 0;
	result.val[3][3] = 1;
	return (result);
}
*/
