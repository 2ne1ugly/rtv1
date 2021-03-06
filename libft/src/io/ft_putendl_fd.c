/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:25:35 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/08 10:25:36 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (fd < 0 || s == 0 || fd > 65535)
		return ;
	while (*s)
		if (write(fd, s++, 1) < 0)
			return ;
	if (write(fd, "\n", 1) < 0)
		return ;
}
