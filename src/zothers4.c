/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zothers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:08:57 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/15 12:36:09 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	abs_val(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data->img->addr)
		return ;
	if (data->img->bpp <= 0 || data->img->line_length <= 0)
		return ;
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = data->img->addr + (y * data->img->line_length
			+ x * (data->img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_image(t_data *data)
{
	if (!data)
		return ;
	data->img = malloc(sizeof(t_img));
	if (!data->img)
	{
		write(2, "Failed to allocate img struct\n", 31);
		return ;
	}
	data->img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img->img)
	{
		write(2, "Failed to create image\n", 23);
		free(data->img);
		data->img = NULL;
		return ;
	}
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bpp,
			&data->img->line_length,
			&data->img->endian);
}

int	init_img(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return (0);
	data->img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img->img)
		return (0);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bpp, &data->img->line_length, &data->img->endian);
	return (1);
}
