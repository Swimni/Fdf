/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nettoyage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:05:26 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:30:56 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	int	y;

	if (!fdf || !fdf->map)
		return ;
	y = 0;
	while (y < fdf->height)
	{
		free(fdf->map[y]);
		y++;
	}
	free(fdf->map);
	fdf->map = NULL;
}

static void	free_map_data(t_data *data)
{
	int	y;

	if (data->map && data->map != data->fdf.map)
	{
		y = 0;
		while (y < data->height)
			free(data->map[y++]);
		free(data->map);
		data->map = NULL;
	}
}

static void	free_image(t_data *data)
{
	if (data->img && data->mlx && data->img->img)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		free(data->img);
		data->img = NULL;
	}
}

static void	free_window_and_display(t_data *data)
{
	if (data->win && data->mlx)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	free_map_data(data);
	if (data->line_widths)
	{
		free(data->line_widths);
		data->line_widths = NULL;
	}
	free_fdf(&data->fdf);
	free_image(data);
	free_window_and_display(data);
}
