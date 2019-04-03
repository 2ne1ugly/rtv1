/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:45:40 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 21:44:42 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//if col is NULL, it only returns dist or 0 (if no intersection)
double	ray_to_plane(t_ray *ray, void *obj, t_intersect *out)
{
	double	denom;
	double	t;
	t_vec	temp;
	t_plane	*plane;

	plane = obj;
	denom = vec_dot(&ray->dir, &plane->normal);
	if (fabs(denom) > 0.0001)
	{
		temp = vec_sub(&plane->pos, ray->pos);
		t = vec_dot(&temp, &plane->normal) / denom;
		if (t < 0)
			return (0);
		if (out != NULL)
		{
			out->pos = vec_add(&ray->pos, vec_mul(ray->dir, t));
			out->normal = plane->normal;
			out->dist = t;
		}
		return (t);
	}
	return (0);
}

//i is input, a, b, c. output is int, double, double
//if this give complex result, it returns 0
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

//if ray is inside the sphere, it will work oddly
double	ray_to_sphere(t_ray *ray, void *obj, t_intersect *out)
{
	t_vec		oc;
	double		t0;
	double		t1;
	t_vec		abc;
	t_sphere	*sphere;

	sphere = obj;
	oc = vec_sub(&ray->pos, sphere->pos);
	abc.x = vec_dot(&ray->dir, &ray->dir);
	abc.y = 2 * vec_dot(&ray->dir, &oc);
	abc.z = vec_dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (solv_quad(&abc, &t0, &t1) && t0 > 0)
	{
		if (out != NULL)
		{
			out->pos = vec_add(&ray->pos, vec_mul(ray->dir, t0));
			out->normal = vec_sub(&out->pos, sphere->pos);
			out->normal = vec_norm(&out->normal);
			out->dist = t0;
		}
		return (t0);
	}
	return (0);
}

/*
//https://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf
double	ray_to_cylinder(t_ray *ray, t_cylinder *cylinder, t_intersect *out)
{
	t_vec	oc;
	double	a;
	double	b;
	double	t;
	double	disc;

	oc = vec_sub(&ray->pos, &sphere->pos)
	a = vec_dot(&ray->dir, &ray->dir);
	b = vec_dot(&oc, &ray->dir) * 2.0;
	disc = b * b - 4 * a * vec_dot(&oc,&oc) - sphere->radius * sphere->radius;
    if(disc < 0)
		return (0);
    t = -(b + sqrt(disc)) / (2.0 * a);
	if (out != NULL)
	{
		oc = vec_mul(&ray->dir, t);
		out->pos = vec_add(&ray->pos, &oc);
		oc = vec_sub(&out->pos, &sphere->pos)
		out->normal = vec_norm(&oc);
		out->dist = t;
	}
	return (t);
}
*/
