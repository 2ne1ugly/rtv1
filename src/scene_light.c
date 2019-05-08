/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:16:27 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/08 12:41:20 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <libft.h>

t_light	*new_scene_light(t_app *app)
{
	t_light *old;
	t_light *new;

	if (app->scene.lights == NULL)
	{
		app->scene.lights = malloc(sizeof(t_light));
		app->scene.lights->next = NULL;
		return (app->scene.lights);
	}
	new = malloc(sizeof(t_light));
	old = app->scene.lights;
	new->next = old;
	app->scene.lights = new;
	return (new);
}

void	add_scene_light(t_app *app, t_vec *pos)
{
	t_light *light;

	light = new_scene_light(app);
	light->pos = *pos;
}
