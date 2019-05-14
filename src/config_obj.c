/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:04:24 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/13 17:35:14 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtv1.h>
#include <stdlib.h>

int		parse_sphere(t_app *app, char **str)
{
	char	**coords;
	double	radius;
	int		color;
	t_vec	pos;

	if (array_len(str) != 4)
		return (0);
	coords = ft_strsplit(str[1], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	pos.x = ft_atof(coords[0]);
	pos.y = ft_atof(coords[1]);
	pos.z = ft_atof(coords[2]);
	radius = ft_atof(str[2]);
	color = (int)ft_strtol(str[3]);
	add_scene_sphere(app, &pos, radius, color);
	return (del_tab(coords) + 1);
}

int		parse_cylinder(t_app *app, char **str)
{
	char	**coords;
	t_vec	rot;
	int		color;
	t_vec	pos;

	if (array_len(str) != 5)
		return (0);
	coords = ft_strsplit(str[1], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	pos.x = ft_atof(coords[0]);
	pos.y = ft_atof(coords[1]);
	pos.z = ft_atof(coords[2]);
	free_tab(coords);
	coords = ft_strsplit(str[2], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	rot.x = ft_atof(coords[0]);
	rot.y = ft_atof(coords[1]);
	rot.z = ft_atof(coords[2]);
	rot.w = ft_atof(str[3]);
	color = (int)ft_strtol(str[4]);
	add_scene_cylinder(app, &pos, &rot, color);
	return (del_tab(coords) + 1);
}

int		parse_cone(t_app *app, char **str)
{
	char	**coords;
	t_vec	rot;
	int		color;
	t_vec	pos;

	if (array_len(str) != 5)
		return (0);
	coords = ft_strsplit(str[1], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	pos.x = ft_atof(coords[0]);
	pos.y = ft_atof(coords[1]);
	pos.z = ft_atof(coords[2]);
	free_tab(coords);
	coords = ft_strsplit(str[2], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	rot.x = ft_atof(coords[0]);
	rot.y = ft_atof(coords[1]);
	rot.z = ft_atof(coords[2]);
	rot.w = ft_atof(str[3]);
	color = (int)ft_strtol(str[4]);
	add_scene_cone(app, &pos, &rot, color);
	return (del_tab(coords) + 1);
}

int		parse_plane(t_app *app, char **str)
{
	char	**coords;
	t_vec	rot;
	int		color;
	t_vec	pos;

	if (array_len(str) != 4)
		return (0);
	coords = ft_strsplit(str[1], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	pos.x = ft_atof(coords[0]);
	pos.y = ft_atof(coords[1]);
	pos.z = ft_atof(coords[2]);
	free_tab(coords);
	coords = ft_strsplit(str[2], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	rot.x = ft_atof(coords[0]);
	rot.y = ft_atof(coords[1]);
	rot.z = ft_atof(coords[2]);
	color = (int)ft_strtol(str[3]);
	add_scene_plane(app, &pos, &rot, color);
	return (del_tab(coords) + 1);
}
