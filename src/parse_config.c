/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:14:10 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/16 15:13:15 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rtv1.h>
#include <fcntl.h>

void	parse_objects(t_app *app, char **split, char *str)
{
	if (ft_strequ(split[0], "sphere"))
		if (!parse_sphere(app, split))
			ft_fprintf(2, "Error parsing line: %s", str);
	if (ft_strequ(split[0], "cylinder"))
		if (!parse_cylinder(app, split))
			ft_fprintf(2, "Error parsing line: %s", str);
	if (ft_strequ(split[0], "cone"))
		if (!parse_cone(app, split))
			ft_fprintf(2, "Error parsing line: %s", str);
	if (ft_strequ(split[0], "plane"))
		if (!parse_plane(app, split))
			ft_fprintf(2, "Error parsing line: %s", str);
}

void	parse_misc(t_app *app, char **split, char *str)
{
	if (ft_strequ(split[0], "light"))
		if (!parse_light(app, split))
			ft_fprintf(2, "Error parsing line: %s", str);
	if (ft_strequ(split[0], "cam"))
		if (!parse_cam(app, split))
			ft_fprintf(2, "Error parsing line: %s", str);
}

void	parse_config(t_app *app, char *file)
{
	char	*str;
	char	**split;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("No such file.\n");
		exit(1);
	}
	while (get_next_line(fd, &str, 64))
	{
		split = ft_strsplit(str, ' ');
		parse_objects(app, split, str);
		parse_misc(app, split, str);
		free_tab(split);
		ft_strdel(&str);
	}
}
