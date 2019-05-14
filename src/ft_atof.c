/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:18:31 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/13 17:36:05 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_atof(char *str)
{
	double	res;
	int		tmp;
	double	mult;
	int		neg;

	neg = *str == '-' ? -1 : 1;
	tmp = ft_atoi(str);
	res = (double)tmp;
	mult = 0.1;
	if ((str = ft_strchr(str, '.')))
	{
		str++;
		while (*str && *str >= '0' && *str <= '9')
		{
			res += mult * (*str - '0') * neg;
			mult *= 0.1;
			str++;
		}
	}
	return (res);
}
