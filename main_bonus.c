/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:57:39 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:30:15 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	init_proj_bonus(&data.proj_bonus);
	mlx_loop_hook(data.mlx, render_frame_bonus, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hook_bonus, &data);
	mlx_hook(data.win, 17, 0, close_win, &data);
	mlx_loop(data.mlx);
	return (0);
}
