/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projec_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:16:37 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 14:02:13 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_line_bonus(t_fdf *fdf, t_data *data, int y, int x)
{
	t_line	line;
	int		proj_start[2];
	int		proj_end[2];

	line.start = fdf->map[y][x];
	line.end = fdf->map[y][x + 1];
	iso_project_bonus(line.start, &data->proj_bonus, proj_start);
	iso_project_bonus(line.end, &data->proj_bonus, proj_end);
	line.x0 = proj_start[0];
	line.y0 = proj_start[1];
	line.x1 = proj_end[0];
	line.y1 = proj_end[1];
	line.color_start = get_color_from_height(line.start.z,
			data->z_min, data->z_max);
	line.color_end = get_color_from_height(line.end.z,
			data->z_min, data->z_max);
	draw_line(data, &line);
}

static void	draw_vertical_line_bonus(t_fdf *fdf, t_data *data, int y, int x)
{
	t_line	line;
	int		proj_start[2];
	int		proj_end[2];

	line.start = fdf->map[y][x];
	line.end = fdf->map[y + 1][x];
	iso_project_bonus(line.start, &data->proj_bonus, proj_start);
	iso_project_bonus(line.end, &data->proj_bonus, proj_end);
	line.x0 = proj_start[0];
	line.y0 = proj_start[1];
	line.x1 = proj_end[0];
	line.y1 = proj_end[1];
	line.color_start = get_color_from_height(line.start.z,
			data->z_min, data->z_max);
	line.color_end = get_color_from_height(line.end.z,
			data->z_min, data->z_max);
	draw_line(data, &line);
}

void	draw_map_bonus(t_fdf *fdf, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (x + 1 < fdf->width)
				draw_horizontal_line_bonus(fdf, data, y, x);
			if (y + 1 < fdf->height)
				draw_vertical_line_bonus(fdf, data, y, x);
			x++;
		}
		y++;
	}
}

int	close_win_bonus(t_data *data)
{
	if (!data)
		return (0);
	return (close_win((void *)data));
}

void	redraw_bonus(t_data *data)
{
	render_frame_bonus(data);
}
