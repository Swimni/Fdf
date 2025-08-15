/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:10:39 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/08 10:57:12 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_key_bonus(int keycode, t_proj_bonus *proj_bonus)
{
	if (keycode == KEY_LEFT)
		move_bonus(proj_bonus, -10, 0);
	else if (keycode == KEY_RIGHT)
		move_bonus(proj_bonus, 10, 0);
	else if (keycode == KEY_UP)
		move_bonus(proj_bonus, 0, -10);
	else if (keycode == KEY_DOWN)
		move_bonus(proj_bonus, 0, 10);
}

void	rotate_key_bonus(int keycode, t_proj_bonus *proj_bonus)
{
	if (keycode == KEY_ROTATE_X)
		rotate_bonus(proj_bonus, 0.1f, 0.0f, 0.0f);
	else if (keycode == KEY_ROTATE_Y)
		rotate_bonus(proj_bonus, 0.0f, 0.1f, 0.0f);
	else if (keycode == KEY_ROTATE_Z)
		rotate_bonus(proj_bonus, 0.0f, 0.0f, 0.1f);
}

int	key_hook_bonus(int keycode, t_data *data)
{
	if (!data)
		return (0);
	if (keycode == KEY_PLUS)
		zoom_bonus(&data->proj_bonus, 1.1f);
	else if (keycode == KEY_MINUS)
		zoom_bonus(&data->proj_bonus, 0.9f);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		move_key_bonus(keycode, &data->proj_bonus);
	else if (keycode == KEY_ROTATE_X || keycode == KEY_ROTATE_Y
		|| keycode == KEY_ROTATE_Z)
		rotate_key_bonus(keycode, &data->proj_bonus);
	else if (keycode == KEY_ESC)
		close_win_bonus(data);
	redraw_bonus(data);
	return (0);
}
