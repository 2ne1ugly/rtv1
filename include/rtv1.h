/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 23:01:58 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 21:45:40 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define PI 3.14159265359
# define MAGENTA 0x00FF00

# define X 0
# define Y 1
# define Z 2

# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))

# include <mlx.h>
# include <stdlib.h>
# include <libft.h>
# include <math.h>

typedef unsigned int	t_uint;

typedef struct	s_mat
{
	double val[4][4];
}				t_mat;

typedef struct	s_vec
{
	double x;
	double y;
	double z;
	double w;
}				t_vec;

typedef struct	s_ray
{
	t_vec	pos;
	t_vec	dir;
}				t_ray;

typedef struct	s_cam
{
	t_vec	pos;
	t_vec	dir;
	double	fov;
	double	near;
	//for calculation
	t_vec	x_axis;
	t_vec	y_axis;
	t_vec	z_axis;
}				t_cam;

typedef struct	s_img
{
	char	*ptr;
	char	*data_addr;
	int		sl;
	int		bpp;
	int		endian;
}				t_img;

//	All normals and directions has to be normalized.
typedef struct	s_intersect
{
	t_vec	pos;
	t_vec	normal;
	double	dist;
}				t_intersect;

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

typedef struct	s_cone
{
	t_vec	pos;
	t_vec	rot;
	double	radius;
	double	height;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec	pos;
	t_vec	rot;
	double	radius;
	double	height;
}				t_cylinder;

typedef struct	s_light
{
	t_vec	pos;
}				t_light;

typedef struct	s_obj
{
	void			*obj;
	double			(*ray_to_obj)(t_ray *, void *, t_intersect *);
	struct s_obj	*next;
}				t_obj;

typedef struct	s_scene
{
	t_obj	*objects;
	t_light	*lights;
}				t_scene;

typedef struct	s_app
{
	void		*mlx_handle;
	void		*wnd_handle;
	int			width;
	int			height;
	t_img		img;
	double		aspect;	//width / height
	t_cam		cam;
	t_ray		**screen_ray;
	t_scene		scene;
}				t_app;

int				app_looper(void *param);

void			img_pixel_put(t_app *app, int x, int y, int color);
int				init_app(t_app **app);

double			vec_dot(t_vec *lhs, t_vec *rhs);
t_vec			vec_cross(t_vec *lhs, t_vec *rhs);
double			vec_abs(t_vec *vec);
t_vec			vec_norm(t_vec *vec);
t_vec			vec_mul(t_vec lhs, double rhs);
t_vec			vec_add(t_vec *lhs, t_vec rhs);
t_vec			vec_sub(t_vec *lhs, t_vec rhs);

void			set_rays(t_app *app);
void			shoot_rays(t_app *app);
void			set_basis(t_cam *cam);

double			ray_to_plane(t_ray *ray, void *obj, t_intersect *out);
double			ray_to_sphere(t_ray *ray, void *obj, t_intersect *out);
#endif