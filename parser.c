/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:43:48 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 13:06:18 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *filename)
{
	int		fd;
	char	*line;
	char	**split;
	int		width;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	width = 0;
	i = 0;
	while (split && split[i])
	{
		width++;
		i++;
	}
	free_split(split);
	free(line);
	close(fd);
	return (width);
}
