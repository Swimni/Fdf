/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:58:35 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:32:13 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_width(char *line)
{
	char	**split;
	int		width;

	width = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	while (split[width])
		width++;
	free_split(split);
	return (width);
}

static int	count_height(int fd)
{
	int		height;
	char	*line;

	height = 1;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (height);
}

static char	*read_first_line(int fd)
{
	return (get_next_line(fd));
}

void	get_width_and_height(char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		width;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = read_first_line(fd);
	if (!line)
	{
		close(fd);
		return ;
	}
	width = count_width(line);
	free(line);
	if (width < 0)
	{
		close(fd);
		return ;
	}
	height = count_height(fd);
	close(fd);
	fdf->width = width;
	fdf->height = height;
}

void	clear_image(t_data *data)
{
	int	i;
	int	*pixels;

	pixels = (int *)data->img->addr;
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		pixels[i] = 0x000000;
		i++;
	}
}
