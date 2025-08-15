/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:31:20 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:30:38 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	if (!data)
		return (0);
	if (data->img && data->img->img)
		mlx_destroy_image(data->mlx, data->img->img);
	if (data->img)
		free(data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->line_widths)
	{
		free(data->line_widths);
		data->line_widths = NULL;
	}
	if (data->map)
	{
		free_fdf(&data->fdf);
		data->map = NULL;
	}
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
	t_data		data;
	t_map_info	map_info;

	if (argc != 2)
		return (write(2, "Usage: ./fdf map.fdf\n", 22), 1);
	if (!parse_and_init(argv[1], &fdf, &data))
		return (1);
	data.fdf = fdf;
	map_info.map = fdf.map;
	map_info.height = fdf.height;
	map_info.width = fdf.width;
	find_z_min_max(&map_info, &data.z_min, &data.z_max);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_press, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	return (0);
}
