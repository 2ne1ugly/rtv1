/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:21:11 by zfaria            #+#    #+#             */
/*   Updated: 2019/01/01 12:23:33 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int num)
{
	if (num < 0 && num != -2147483648)
		return (-num);
	return (num);
}
