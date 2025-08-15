/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:10:52 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 13:08:18 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_proj_bonus(t_proj_bonus *proj_bonus)
{
	if (!proj_bonus)
		return ;
	proj_bonus->zoom = 1.0f;
	proj_bonus->offset_x = 0.0f;
	proj_bonus->offset_y = 0.0f;
	proj_bonus->angle_x = 0.0f;
	proj_bonus->angle_y = 0.0f;
	proj_bonus->angle_z = 0.0f;
}

void	zoom_bonus(t_proj_bonus *proj_bonus, float factor)
{
	if (!proj_bonus)
		return ;
	proj_bonus->zoom *= factor;
	if (proj_bonus->zoom < 0.1f)
		proj_bonus->zoom = 0.1f;
	if (proj_bonus->zoom > 10.0f)
		proj_bonus->zoom = 10.0f;
}

void	move_bonus(t_proj_bonus *proj_bonus, float dx, float dy)
{
	if (!proj_bonus)
		return ;
	proj_bonus->offset_x += dx;
	proj_bonus->offset_y += dy;
}

void	rotate_bonus(t_proj_bonus *proj_bonus,
float d_angle_x, float d_angle_y, float d_angle_z)
{
	if (!proj_bonus)
		return ;
	proj_bonus->angle_x += d_angle_x;
	proj_bonus->angle_y += d_angle_y;
	proj_bonus->angle_z += d_angle_z;
	while (proj_bonus->angle_x > 6.283185f)
		proj_bonus->angle_x -= 6.283185f;
	while (proj_bonus->angle_x < 0.0f)
		proj_bonus->angle_x += 6.283185f;
	while (proj_bonus->angle_y > 6.283185f)
		proj_bonus->angle_y -= 6.283185f;
	while (proj_bonus->angle_y < 0.0f)
		proj_bonus->angle_y += 6.283185f;
	while (proj_bonus->angle_z > 6.283185f)
		proj_bonus->angle_z -= 6.283185f;
	while (proj_bonus->angle_z < 0.0f)
		proj_bonus->angle_z += 6.283185f;
}

int	render_frame_bonus(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data || !data->mlx || !data->win || !data->img || !data->img->img)
		return (0);
	ft_bzero(data->img->addr, WIN_WIDTH * WIN_HEIGHT * (data->img->bpp / 8));
	draw_map_bonus(&data->fdf, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
