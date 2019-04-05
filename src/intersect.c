/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:45:40 by mchi              #+#    #+#             */
/*   Updated: 2019/04/04 22:12:19 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

//if col is NULL, it only returns dist or 0 (if no intersection)
double	ray_to_plane(t_ray *ray, t_obj *obj, t_intersect *out)
{
	double	denom;
	double	t;
	t_vec	temp;
	t_plane	*plane;

	plane = obj->obj;
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
			out->obj = obj;
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
double	ray_to_sphere(t_ray *ray, t_obj *obj, t_intersect *out)
{
	t_vec		oc;
	double		t0;
	double		t1;
	t_vec		abc;
	t_sphere	*sphere;

	sphere = obj->obj;
	oc = vec_sub(&ray->pos, sphere->pos);
	abc.x = vec_dot2(&ray->dir);
	abc.y = 2 * vec_dot(&ray->dir, &oc);
	abc.z = vec_dot2(&oc) - sphere->radius * sphere->radius;
	if (solv_quad(&abc, &t0, &t1) && t0 > 0)
	{
		if (out != NULL)
		{
			out->pos = vec_add(&ray->pos, vec_mul(ray->dir, t0));
			out->normal = vec_sub(&out->pos, sphere->pos);
			out->normal = vec_norm(&out->normal);
			out->dist = t0;
			out->obj = obj;
		}
		return (t0);
	}
	return (0);
}

double	ray_to_cylinder(t_ray *ray, t_obj *obj, t_intersect *out)
{
	t_vec		oc;
	double		t0;
	double		t1;
	t_cyl		*cyl;
	t_vec		abc;

	cyl = obj->obj;
	oc = vec_sub(&ray->pos, cyl->pos);
	cyl->a = vec_sub_mul(&ray->dir, &cyl->dir);
	cyl->c = vec_sub_mul(&oc, &cyl->dir);
	abc.x = vec_dot2(&cyl->a);
	abc.y = 2 * vec_dot(&cyl->a, &cyl->c);
	abc.z = vec_dot2(&cyl->c) - cyl->radius * cyl->radius;
	if (solv_quad(&abc, &t0, &t1) && t0 > 0)
	{
		if (out != NULL)
		{
			out->pos = vec_add(&ray->pos, vec_mul(ray->dir, t0));
			out->normal = find_cyl_norm(cyl, out->pos);
			out->dist = t0;
			out->obj = obj;
		}
		return (t0);
	}
	return (0);
}

t_vec	find_cone_abc(t_ray *ray, t_cone *cone)
{
	t_vec		oc;
	t_vec		abc;
	t_vec		tmp;
	t_vec		tmp2;

	oc = vec_sub(&ray->pos, cone->pos);
	tmp = vec_sub_mul(&ray->dir, &cone->dir);
	abc.x = cone->c2a * vec_dot2(&tmp) -
		cone->s2a * pow(vec_dot(&ray->dir, &cone->dir), 2);
	tmp2 = vec_sub_mul(&oc, &cone->dir);
	abc.y = 2 * (cone->c2a * vec_dot(&tmp, &tmp2) -
		cone->s2a * vec_dot(&ray->dir, &cone->dir) *
		vec_dot(&oc, &cone->dir));
	abc.z = cone->c2a * vec_dot2(&tmp2) -
		cone->s2a * pow(vec_dot(&oc, &cone->dir), 2);
	return (abc);
}

double	ray_to_cone(t_ray *ray, t_obj *obj, t_intersect *out)
{
	double		t0;
	double		t1;
	t_cone		*cone;
	t_vec		abc;

	cone = obj->obj;
	abc = find_cone_abc(ray, cone);
	if (solv_quad(&abc, &t0, &t1) && t0 > 0)
	{
		if (out != NULL)
		{
			out->pos = vec_add(&ray->pos, vec_mul(ray->dir, t0));
			out->normal = find_cone_norm(cone, out->pos);
			out->dist = t0;
			out->obj = obj;
		}
		return (t0);
	}
	return (0);
}
