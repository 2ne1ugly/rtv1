/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 04:28:48 by mchi              #+#    #+#             */
/*   Updated: 2019/04/03 11:46:13 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		vec_sub(t_vec *lhs, t_vec rhs)
{
	rhs.x = lhs->x - rhs.x;
	rhs.y = lhs->y - rhs.y;
	rhs.z = lhs->z - rhs.z;
	rhs.w = lhs->w || rhs.w;
	return (rhs);
}

t_vec		vec_add(t_vec *lhs, t_vec rhs)
{
	rhs.x += lhs->x;
	rhs.y += lhs->y;
	rhs.z += lhs->z;
	rhs.w = lhs->w || rhs.w;
	return (rhs);
}

double		vec_dot2(t_vec *lhs)
{
	double	val;

	val = lhs->x * lhs->x;
	val += lhs->y * lhs->y;
	val += lhs->z * lhs->z;
	return (val);
}
