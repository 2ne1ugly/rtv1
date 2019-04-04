
#include "rtv1.h"

t_vec	find_cyl_norm(t_cyl	*cyl, t_vec pos)
{
	t_vec lhs;
	t_vec rhs;

	lhs = vec_sub(&pos, cyl->pos);
	rhs = vec_mul(cyl->dir, vec_dot(&lhs, &cyl->dir));
	rhs = vec_sub(&lhs, rhs);
	return (vec_norm(&rhs));
}

//there's a chance that this wont work
t_vec	find_cone_norm(t_cone *cone, t_vec pos)
{
	t_vec lhs;
	t_vec rhs;

	lhs = vec_sub(&pos, cone->pos);
	rhs = vec_mul(cone->dir, vec_dot(&lhs, &cone->dir));
	rhs = vec_sub(&lhs, rhs);
	rhs = vec_norm(&rhs);
	rhs = vec_mul(rhs, cos(cone->alpha));
	rhs = vec_add(&rhs,	vec_mul(cone->dir, sin(cone->alpha)));
	return (vec_norm(&rhs));
}
