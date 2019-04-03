/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:30:32 by mchi              #+#    #+#             */
/*   Updated: 2019/04/02 20:43:42 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "rtv1.h"

int	app_key_press(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)keycode;
	return (0);
}

int	app_key_release(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)keycode;
	return (0);
}
