/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zothers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:01:21 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:32:29 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Convertit t_point en tableau float [x, y, z]
static void	point_to_vec3f(t_point p, float vec[3])
{
	vec[0] = (float)p.x;
	vec[1] = (float)p.y;
	vec[2] = (float)p.z;
}

// Applique les rotations sur vec[3] in place
static void	apply_rotations(float vec[3], t_proj_bonus *proj_bonus)
{
	float	y_rot;
	float	x_rot;
	float	z_rot;

	y_rot = vec[1] * cosf(proj_bonus->angle_x) - vec[2]
		* sinf(proj_bonus->angle_x);
	vec[2] = vec[1] * sinf(proj_bonus->angle_x) + vec[2]
		* cosf(proj_bonus->angle_x);
	vec[1] = y_rot;
	x_rot = vec[0] * cosf(proj_bonus->angle_y) + vec[2]
		* sinf(proj_bonus->angle_y);
	vec[2] = -vec[0] * sinf(proj_bonus->angle_y) + vec[2]
		* cosf(proj_bonus->angle_y);
	vec[0] = x_rot;
	z_rot = vec[0] * cosf(proj_bonus->angle_z) - vec[1]
		* sinf(proj_bonus->angle_z);
	vec[1] = vec[0] * sinf(proj_bonus->angle_z) + vec[1]
		* cosf(proj_bonus->angle_z);
	vec[0] = z_rot;
}

void	iso_project_bonus(t_point p, t_proj_bonus
*proj_bonus, int proj_point[2])
{
	float	vec[3];

	if (!proj_bonus)
		return ;
	point_to_vec3f(p, vec);
	apply_rotations(vec, proj_bonus);
	proj_point[0] = (int)((vec[0] - vec[1]) * proj_bonus->zoom)
		+ (int)proj_bonus->offset_x;
	proj_point[1] = (int)((vec[0] + vec[1]) * proj_bonus->zoom
			/ 2.0f - vec[2] * proj_bonus->zoom) + (int)proj_bonus->offset_y;
}
