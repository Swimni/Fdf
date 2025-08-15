/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:02:53 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:31:58 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color_from_height(int z, int z_min, int z_max)
{
	double	ratio;

	if (z_max == z_min)
		return (0xFFFFFF);
	ratio = (double)(z - z_min) / (double)(z_max - z_min);
	if (ratio < 0.3)
		return (0x0000FF);
	else if (ratio < 0.6)
		return (0x00FF00);
	else
		return (0xFF0000);
}

static void	find_z_min_max_in_line(t_point *line,
	int width, int *z_min, int *z_max)
{
	int	x;

	x = 0;
	while (x < width)
	{
		if (line[x].z < *z_min)
			*z_min = line[x].z;
		if (line[x].z > *z_max)
			*z_max = line[x].z;
		x++;
	}
}

void	find_z_min_max(t_map_info *info, int *z_min, int *z_max)
{
	int	y;

	y = 0;
	*z_min = info->map[0][0].z;
	*z_max = info->map[0][0].z;
	while (y < info->height)
	{
		find_z_min_max_in_line(info->map[y], info->width, z_min, z_max);
		y++;
	}
}
