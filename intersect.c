typedef struct	s_vec
{
	double x;
	double y;
	double z;
}				t_vec;

//	All normals and directions has to be normalized.
typedef struct	s_ray
{
	t_vec	pos;
	t_vec	dir;
}				t_ray;

typedef struct	t_intersect
{
	t_vec	pos;
	t_vec	normal;
	double	dist;
}				s_intersect;

typedef struct	s_sphere
{
	t_vec	pos;
	t_vec	rot;
	double	radius;
}				t_sphere;

typedef struct	s_plane
{
	t_vec	pos;
	t_vec	rot;

	//calculation
	t_vec	normal;
}				t_plane;

typedef struct	s_cone;
{
	t_vec	pos;
	t_vec	rot;
	double	radius;
	double	height;
}				t_cone;

typedef struct	s_cylinder;
{
	t_vec	pos;
	t_vec	rot;
	double	radius;
	double	height;
}				t_cylinder;

//if col is NULL, it only returns dist or 0 (if no intersection)
double	ray_to_plane(t_ray *ray, t_plane *plane, t_intersect *out)
{
	double	denom;
	double	t;
	t_vec	temp;

	denom = vec_dot(&ray->dir, &plane->normal);
	if (fabs(denom) > 0.0001)
	{
    	temp = vec_sub(&plane->pos, &ray->pos);
		t = vec_dot(&temp, &plane->normal) / denom;
    	if (t < 0)
            return (0);
		if (out != NULL)
		{
			temp = vec_mul(&ray->dir, t);
			out->pos = vec_add(&ray->pos, &temp);
			out->normal = plane->normal;
			out->dist = t;
		}
		return (t);
	}
	return (0);
}

int 	solv_quad(t_vec i, double *x0, double *x1) 
{ 
    double disc;
	double q;

	disc = i.y * i.y - 4 * i.x * i.z; 
	if (discr < 0)
		return (0);
	if (b > 0)
		q = -0.5 * (b + sqrt(discr))
	else
        q = -0.5 * (b - sqrt(discr)); 
	*x0 = q / a; 
	*x1 = c / q; 

	if (*x0 > *x1)
	{
		q = *x0;
		*x0 = *x1;
		*x1 = q;
	}
    return 1; 
} 

//it may have problems.
double	ray_to_sphere(t_ray *ray, t_sphere *sphere, t_intersect *out)
{
	t_vec	oc;
	double	a;
	double	b;
	double	t;
	double	disc;
	oc = vec_sub(&ray->pos, &sphere->pos)
	if (vec_abs(&oc) <= sphere->radius)
		return (0);
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
