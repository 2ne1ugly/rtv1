/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:16:49 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 20:39:03 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

double		vec_dot(t_vec *lhs, t_vec *rhs)
{
	double	result;

	result = 0;
	result += lhs->x * rhs->x;
	result += lhs->y * rhs->y;
	result += lhs->z * rhs->z;
	return (result);
}

t_vec		vec_cross(t_vec *lhs, t_vec *rhs)
{
	t_vec result;

	result.x = lhs->y * rhs->z - lhs->z * rhs->y;
	result.y = -lhs->x * rhs->z + lhs->z * rhs->x;
	result.z = lhs->x * rhs->y - lhs->y * rhs->x;
	result.w = 0;
	return (result);
}

double		vec_abs(t_vec *vec)
{
	double		result;

	result = vec->x * vec->x;
	result += vec->y * vec->y;
	result += vec->z * vec->z;
	return (sqrt(result));
}

t_vec		vec_norm(t_vec *vec)
{
	t_vec	result;
	double	length;

	length = vec_abs(vec);
	result.x = vec->x / length;
	result.y = vec->y / length;
	result.z = vec->z / length;
	return (result);
}

t_vec		vec_mul(t_vec lhs, double rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return (lhs);
}
