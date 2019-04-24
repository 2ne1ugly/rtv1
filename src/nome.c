/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nome.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:38:39 by mchi              #+#    #+#             */
/*   Updated: 2019/04/11 17:38:40 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

int 	solv_quad(t_vec *i, double *x0, double *x1)
{
	double disc;
	double q;

	disc = i->y * i->y - 4 * i->x * i->z;
	if (disc < 0)
		return (0);
	*x0 = -i->y + sqrt(disc);
	*x1 = -i->y - sqrt(disc);
	*x0 /= 2 * i->x;
	*x1 /= 2 * i->x;
	if (*x0 > *x1)
	{
		q = *x0;
		*x0 = *x1;
		*x1 = q;
	}
	return (1);
}

t_vec	find_cyl_norm(t_cyl *cyl, t_vec pos)
{
	t_vec lhs;
	t_vec rhs;

	lhs = vec_sub(&pos, cyl->pos);
	rhs = vec_mul(cyl->dir, vec_dot(&lhs, &cyl->dir));
	rhs = vec_sub(&lhs, rhs);
	return (vec_norm(&rhs));
}

t_vec	find_cone_norm(t_cone *cone, t_vec pos)
{
	t_vec lhs;
	t_vec rhs;

	lhs = vec_sub(&pos, cone->pos);
	rhs = vec_mul(cone->dir, vec_dot(&lhs, &cone->dir));
	rhs = vec_sub(&lhs, rhs);
	rhs = vec_norm(&rhs);
	rhs = vec_mul(rhs, cos(cone->alpha));
	rhs = vec_add(&rhs, vec_mul(cone->dir, sin(cone->alpha)));
	return (vec_norm(&rhs));
}
