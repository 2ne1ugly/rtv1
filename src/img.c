/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:08:47 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 20:40:22 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	img_pixel_put(t_app *app, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= app->width || y >= app->height)
		return ;
	*(int *)(app->img.data_addr + (x + y * app->width) * app->img.bpp) = color;
}
