/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:34:42 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:31:38 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	validate_map(t_fdf *fdf)
{
	if (fdf->height <= 0 || fdf->width <= 0)
	{
		write(2, "Erreur: map vide ou mauvaise taille\n", 36);
		free_fdf(fdf);
		return (0);
	}
	return (1);
}

static void	init_data_from_fdf(t_data *data, t_fdf *fdf)
{
	data->map = fdf->map;
	data->height = fdf->height;
	data->width = fdf->width;
	data->color = 0xFFFFFF;
	data->fdf = *fdf;
}

static int	init_line_widths(t_data *data, int height, int width)
{
	int	i;

	data->line_widths = malloc(sizeof(int) * height);
	if (!data->line_widths)
		return (0);
	i = 0;
	while (i < height)
	{
		data->line_widths[i] = width;
		i++;
	}
	return (1);
}

static int	init_mlx_win(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (0);
	}
	return (1);
}

int	parse_and_init(char *file, t_fdf *fdf, t_data *data)
{
	parse_fdf(file, fdf);
	if (!validate_map(fdf))
		return (0);
	init_data_from_fdf(data, fdf);
	if (!init_line_widths(data, fdf->height, fdf->width))
	{
		free_fdf(fdf);
		return (0);
	}
	if (!init_mlx_win(data))
	{
		free(data->line_widths);
		free_fdf(fdf);
		return (0);
	}
	init_image(data);
	init_projection(&data->proj, WIN_WIDTH, WIN_HEIGHT);
	return (1);
}
