/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zothers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:07:47 by nguinot-          #+#    #+#             */
/*   Updated: 2025/08/10 11:33:00 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	extract_component(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}

static int	interpolate_component(int c1, int c2, double t)
{
	return (c1 + (int)((c2 - c1) * t));
}

static int	interp_one_color(int c1, int c2, double t, int shift)
{
	int	comp1;
	int	comp2;

	comp1 = extract_component(c1, shift);
	comp2 = extract_component(c2, shift);
	return (interpolate_component(comp1, comp2, t));
}

int	interpolate_color(int c1, int c2, double t)
{
	int	r;
	int	g;
	int	b;

	r = interp_one_color(c1, c2, t, 16);
	g = interp_one_color(c1, c2, t, 8);
	b = interp_one_color(c1, c2, t, 0);
	return ((r << 16) | (g << 8) | b);
}
