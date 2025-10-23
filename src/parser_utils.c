/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:28:21 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 14:06:53 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_point(t_point *p, int x, int y, char *str)
{
	p->x = x;
	p->y = y;
	p->z = ft_atoi_simple(str);
	p->color = 0xFFFFFF;
}

t_point	*parse_line(char *line, int width, int y)
{
	t_point	*row;
	char	**split;
	int		x;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	row = malloc(sizeof(t_point) * width);
	if (!row)
	{
		free_split(split);
		return (NULL);
	}
	x = 0;
	while (x < width && split[x])
	{
		fill_point(&row[x], x, y, split[x]);
		x++;
	}
	free_split(split);
	return (row);
}

static int	init_fdf_map(char *file, t_fdf *fdf, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		return (0);
	get_width_and_height(file, fdf);
	fdf->map = malloc(sizeof(t_point *) * fdf->height);
	if (!fdf->map)
	{
		close(*fd);
		return (0);
	}
	return (1);
}

static int	fill_fdf_map(int fd, t_fdf *fdf)
{
	int		y;
	char	*line;

	y = 0;
	line = get_next_line(fd);
	while (line && y < fdf->height)
	{
		fdf->map[y] = parse_line(line, fdf->width, y);
		if (!fdf->map[y])
		{
			free(line);
			free_map(fdf->map, y);
			close(fd);
			return (0);
		}
		free(line);
		y++;
		line = get_next_line(fd);
	}
	free(line);
	return (1);
}

void	parse_fdf(char *file, t_fdf *fdf)
{
	int	fd;

	if (!init_fdf_map(file, fdf, &fd))
		return ;
	if (!fill_fdf_map(fd, fdf))
		return ;
	close(fd);
}
