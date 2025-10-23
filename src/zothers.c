/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zothers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:00:54 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:32:41 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_line_vars(t_line_vars *lv, t_line *line)
{
	lv->x0 = line->x0;
	lv->y0 = line->y0;
	lv->x1 = line->x1;
	lv->y1 = line->y1;
	lv->dx = abs_val(lv->x1 - lv->x0);
	lv->dy = abs_val(lv-> y1 - lv->y0);
	if (lv->x0 < lv->x1)
		lv->sx = 1;
	else
		lv->sx = -1;
	if (lv->y0 < lv->y1)
		lv->sy = 1;
	else
		lv->sy = -1;
	lv->err = lv->dx - lv->dy;
}

void	step_x(t_line_vars *lv)
{
	lv->err -= lv->dy;
	lv->x0 += lv->sx;
}

void	step_y(t_line_vars *lv)
{
	lv->err += lv->dx;
	lv->y0 += lv->sy;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**get_last_split(char **new_split)
{
	static char	**saved = NULL;

	if (new_split == (char **)1)
		saved = NULL;
	else if (new_split)
		saved = new_split;
	return (saved);
}
