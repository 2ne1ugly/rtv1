/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:30:46 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/13 12:11:37 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <rtv1.h>

#define THC 1

void	thread_join(pthread_t *threads)
{
	int i;

	i = 0;
	while (i < THC)
	{
		pthread_join(threads[i], 0);
		i++;
	}
}

void	run_threads(t_app *app)
{
	pthread_t	threads[THC];
	int			i;
	t_args		*args;

	set_basis(&app->cam);
	set_rays(app);
	i = 0;
	while (i < THC)
	{
		args = malloc(sizeof(t_args));
		args->index = i;
		args->app = app;
		args->threads = THC;
		pthread_create(&threads[i], NULL, shoot_rays, args);
		i++;
	}
	thread_join(threads);
	mlx_put_image_to_window(app->mlx_handle,
		app->wnd_handle, app->img.ptr, 0, 0);
}
