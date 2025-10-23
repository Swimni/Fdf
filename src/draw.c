/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:26:32 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:28:44 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static double	prepare_line_vars(t_line_vars *lv, t_line *line)
{
	double	total_dist;

	init_line_vars(lv, line);
	total_dist = sqrt((line->x1 - line->x0) * (line->x1 - line->x0)
			+ (line->y1 - line->y0) * (line->y1 - line->y0));
	if (total_dist == 0)
		total_dist = 1;
	return (total_dist);
}

static void	draw_line_pixel(t_data *data, t_line *line,
	t_line_vars *lv, double total_dist)
{
	double	curr_dist;
	double	t;
	int		color;

	if (lv->x0 >= 0 && lv->x0 < WIN_WIDTH
		&& lv->y0 >= 0 && lv->y0 < WIN_HEIGHT)
	{
		curr_dist = sqrt((lv->x0 - line->x0) * (lv->x0 - line->x0)
				+ (lv->y0 - line->y0) * (lv->y0 - line->y0));
		t = curr_dist / total_dist;
		color = interpolate_color(line->color_start, line->color_end, t);
		put_pixel(data, lv->x0, lv->y0, color);
	}
}

static int	update_line_position(t_line_vars *lv)
{
	lv->e2 = 2 * lv->err;
	if (lv->e2 > -lv->dy)
	{
		lv->err -= lv->dy;
		lv->x0 += lv->sx;
	}
	if (lv->e2 < lv->dx)
	{
		lv->err += lv->dx;
		lv->y0 += lv->sy;
	}
	return (lv->x0 != lv->x1 || lv->y0 != lv->y1);
}

void	draw_line(t_data *data, t_line *line)
{
	t_line_vars	lv;
	double		total_dist;

	total_dist = prepare_line_vars(&lv, line);
	while (1)
	{
		draw_line_pixel(data, line, &lv, total_dist);
		if (!update_line_position(&lv))
			break ;
	}
}
