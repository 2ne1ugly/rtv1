/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:25:10 by mchi              #+#    #+#             */
/*   Updated: 2019/04/24 11:36:31 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*add_scene_obj(t_app *app)
{
	t_obj *old;
	t_obj *new;

	if (app->scene.objects == NULL)
	{
		app->scene.objects = malloc(sizeof(t_obj));
		app->scene.objects->next = NULL;
		return (app->scene.objects);
	}
	new = malloc(sizeof(t_obj));
	old = app->scene.objects;
	new->next = old;
	app->scene.objects = new;
	return (new);
}

void	add_scene_sphere(t_app *app, t_vec *pos, double radius, int color)
{
	t_obj		*new;
	t_sphere	*sphere;
	t_mat		tl_mat;

	new = add_scene_obj(app);
	sphere = malloc(sizeof(t_sphere));
	tl_mat = translation_mat(pos);
	vec_transform(&sphere->pos, &(t_vec){0, 0, 0, 1}, &tl_mat);
	sphere->pos = *pos;
	sphere->radius = radius;
	new->obj = sphere;
	new->color = color;
	new->ray_to_obj = ray_to_sphere;
}

void	add_scene_plane(t_app *app, t_vec *pos, t_vec *rot, int color)
{
	t_obj		*new;
	t_plane		*plane;
	t_mat		rot_mat;
	t_mat		tl_mat;

	new = add_scene_obj(app);
	plane = malloc(sizeof(t_plane));
	tl_mat = translation_mat(pos);
	vec_transform(&plane->pos, &(t_vec){0, 0, 0, 1}, &tl_mat);
	new->color = color;
	rot_mat = rotation_mat(rot->x, rot->y, rot->z);
	vec_transform(&plane->normal, &(t_vec){0, 1, 0, 0}, &rot_mat);
	plane->rot = *rot;
	new->obj = plane;
	new->ray_to_obj = ray_to_plane;
}

void	add_scene_cylinder(t_app *app, t_vec *pos, t_vec *rot, int color)
{
	t_obj	*new;
	t_cyl	*cyl;
	t_mat	rot_mat;
	t_mat	tl_mat;

	new = add_scene_obj(app);
	new->color = color;
	new->ray_to_obj = ray_to_cylinder;
	cyl = malloc(sizeof(t_cyl));
	tl_mat = translation_mat(pos);
	vec_transform(&cyl->pos, &(t_vec){0, 0, 0, 1}, &tl_mat);
	cyl->radius = .25;
	cyl->rot = *rot;
	rot_mat = rotation_mat(rot->x, rot->y, rot->z);
	vec_transform(&cyl->dir, &(t_vec){0, 1, 0, 0}, &rot_mat);
	new->obj = cyl;
}

void	add_scene_cone(t_app *app, t_vec *pos, t_vec *rot, int color)
{
	t_obj	*new;
	t_cone	*cone;
	t_mat	rot_mat;
	t_mat	tl_mat;

	new = add_scene_obj(app);
	new->color = color;
	new->ray_to_obj = ray_to_cone;
	cone = malloc(sizeof(t_cone));
	tl_mat = translation_mat(pos);
	vec_transform(&cone->pos, &(t_vec){0, 0, 0, 1}, &tl_mat);
	cone->alpha = rot->w;
	cone->c2a = cos(cone->alpha) * cos(cone->alpha);
	cone->s2a = sin(cone->alpha) * sin(cone->alpha);
	cone->rot = *rot;
	rot_mat = rotation_mat(rot->x, rot->y, rot->z);
	vec_transform(&cone->dir, &(t_vec){0, 1, 0, 0}, &rot_mat);
	new->obj = cone;
}
