/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:50:57 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 13:11:54 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso_project(t_point p, t_proj proj, int result[2])
{
	double	x;
	double	y;
	double	z;
	double	z_scale;

	x = p.x * proj.zoom;
	y = p.y * proj.zoom;
	z = p.z * proj.zoom;
	z_scale = 0.12;
	result[0] = (int)((x - y) * cos(proj.angle)) + proj.x_offset;
	result[1] = (int)(((x + y) * sin(proj.angle))
			- (z * z_scale)) + proj.y_offset;
}

static void	draw_line_between_points(t_point start, t_point end, t_data *data)
{
	t_line		line;
	int			proj_start[2];
	int			proj_end[2];

	iso_project(start, data->proj, proj_start);
	iso_project(end, data->proj, proj_end);
	line.start = start;
	line.end = end;
	line.x0 = proj_start[0];
	line.y0 = proj_start[1];
	line.x1 = proj_end[0];
	line.y1 = proj_end[1];
	line.color_start = get_color_from_height(start.z, data->z_min, data->z_max);
	line.color_end = get_color_from_height(end.z, data->z_min, data->z_max);
	draw_line(data, &line);
}

void	draw_map(t_fdf *fdf, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (x + 1 < fdf->width)
				draw_line_between_points(fdf->map[y][x],
					fdf->map[y][x + 1], data);
			if (y + 1 < fdf->height)
				draw_line_between_points(fdf->map[y][x],
					fdf->map[y + 1][x], data);
			x++;
		}
		y++;
	}
}

void	init_projection(t_proj *proj, int win_width, int win_height)
{
	proj->zoom = 20;
	proj->angle = 0.7854;
	proj->x_offset = win_width / 2;
	proj->y_offset = win_height / 2;
}
