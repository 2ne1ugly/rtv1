/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 23:01:58 by mchi              #+#    #+#             */
/*   Updated: 2019/05/13 17:34:40 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <stdlib.h>
# include <libft.h>
# include <math.h>

# define PI 3.14159265359

# define X 0
# define Y 1
# define Z 2

# define MIN(a,b) (((a)<(b))?(a):(b))

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
	t_vec	rot;
	double	fov;
	double	near;
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
	t_vec	normal;
}				t_plane;

typedef struct	s_cone
{
	t_vec	pos;
	t_vec	rot;
	double	alpha;
	t_vec	dir;
	double	c2a;
	double	s2a;
}				t_cone;

typedef struct	s_cyl
{
	t_vec	pos;
	t_vec	rot;
	double	radius;
	t_vec	dir;
	t_vec	a;
	t_vec	c;
}				t_cyl;

typedef struct	s_light
{
	t_vec			pos;
	struct s_light	*next;
}				t_light;

struct s_obj;

typedef struct	s_intersect
{
	t_vec			pos;
	t_vec			normal;
	double			dist;
	struct s_obj	*obj;
}				t_intersect;

typedef struct	s_obj
{
	void			*obj;
	double			(*ray_to_obj)(t_ray *, struct s_obj *, t_intersect *);
	int				color;
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
	double		aspect;
	t_cam		cam;
	t_ray		**screen_ray;
	t_scene		scene;
}				t_app;

typedef struct	s_args
{
	t_app		*app;
	int			index;
	int			threads;
}				t_args;

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
double			vec_dot2(t_vec *lhs);
t_vec			vec_rflct(t_vec *inc, t_vec *norm);
t_vec			vec_sub_mul(t_vec *lhs, t_vec *rhs);

void			camera_update(t_cam *cam);

void			vec_transform(t_vec *ret, t_vec *vec, t_mat *mat);
t_mat			rotation_mat(double x, double y, double z);
t_mat			translation_mat(t_vec *vec);
void			mat_identity(t_mat *mat);

int				get_color(double diff, double spec, int color);
int				is_blocking_light(t_vec *from, t_obj *obj, t_vec *to);
t_intersect		find_first_intersect(t_ray *ray, t_obj *obj);

void			set_rays(t_app *app);
void			*shoot_rays(void *args);
void			set_basis(t_cam *cam);
void			run_threads(t_app *app);

int				solv_quad(t_vec *i, double *x0, double *x1);

double			ray_to_plane(t_ray *ray, t_obj *obj, t_intersect *out);
double			ray_to_sphere(t_ray *ray, t_obj *obj, t_intersect *out);
double			ray_to_cylinder(t_ray *ray, t_obj *obj, t_intersect *out);
double			ray_to_cone(t_ray *ray, t_obj *obj, t_intersect *out);

int				key_event(int keycode, void *ptr);
int				del_tab(char **arr);

t_vec			find_cone_norm(t_cone *cone, t_vec pos);
t_vec			find_cyl_norm(t_cyl	*cyl, t_vec pos);

void			add_scene_sphere(t_app *app, t_vec *pos, double r, int color);
void			add_scene_plane(t_app *app, t_vec *pos, t_vec *rot, int color);
void			add_scene_cylinder(t_app *app, t_vec *pos, t_vec *rot, int c);
void			add_scene_cone(t_app *app, t_vec *pos, t_vec *rot, int color);

void			add_scene_light(t_app *app, t_vec *pos);

void			parse_config(t_app *app, char *conf);
int				parse_cylinder(t_app *app, char **str);
int				parse_cone(t_app *app, char **str);
int				parse_sphere(t_app *app, char **str);
int				parse_plane(t_app *app, char **str);
int				parse_light(t_app *app, char **str);
int				parse_cam(t_app *app, char **str);

double 			ft_atof(char *str);
long			ft_strtol(char *str);

#endif
