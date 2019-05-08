/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:22:29 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/08 12:41:12 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		del_tab(char **arr)
{
	free_tab(arr);
	return (0);
}

int		parse_light(t_app *app, char **str)
{
	char	**coords;
	t_vec	pos;

	if (array_len(str) != 2)
		return (0);
	coords = ft_strsplit(str[1], ',');
	if (array_len(coords) != 3)
		return (del_tab(coords));
	pos.x = atof(coords[0]);
	pos.y = atof(coords[1]);
	pos.z = atof(coords[2]);
	add_scene_light(app, &pos);
	return (del_tab(coords) + 1);
}

int		parse_cam(t_app *app, char **str)
{
	char	**c;

	if (array_len(str) != 5)
		return (0);
	c = ft_strsplit(str[1], ',');
	if (array_len(c) != 3)
		return (del_tab(c));
	app->cam.pos = (t_vec){atof(c[0]), atof(c[1]), atof(c[2]), 0};
	free_tab(c);
	c = ft_strsplit(str[2], ',');
	app->cam.rot = (t_vec){atof(c[0]), atof(c[1]), atof(c[2]), 1};
	app->cam.fov = atof(str[3]);
	app->cam.near = atof(str[4]);
	return (del_tab(c) + 1);
}
