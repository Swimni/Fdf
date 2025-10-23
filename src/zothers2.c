/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zothers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:06:08 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:32:51 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cleanup(data);
	exit(0);
	return (0);
}

int	ft_atoi_simple(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

void	free_map(t_point **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	render_frame(t_data *data)
{
	if (!data || !data->img || !data->img->img)
		return (0);
	clear_image(data);
	draw_map(&data->fdf, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
