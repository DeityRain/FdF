/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:21:05 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/28 14:27:39 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color_rgb	get_rgb(int color)
{
	t_color_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	interpolate_color(int start_color, int end_color, float ratio)
{
	t_color_rgb	start_rgb;
	t_color_rgb	end_rgb;
	t_color_rgb	result_rgb;

	if (ratio <= 0.0)
		return (start_color);
	if (ratio >= 1.0)
		return (end_color);
	start_rgb = get_rgb(start_color);
	end_rgb = get_rgb(end_color);
	result_rgb.r = start_rgb.r + (int)((end_rgb.r - start_rgb.r) * ratio);
	result_rgb.g = start_rgb.g + (int)((end_rgb.g - start_rgb.g) * ratio);
	result_rgb.b = start_rgb.b + (int)((end_rgb.b - start_rgb.b) * ratio);
	return (create_color(result_rgb.r, result_rgb.g, result_rgb.b));
}

int	calculate_line_distance(t_point start, t_point end)
{
	int	dx;
	int	dy;

	dx = abs((int)end.x - (int)start.x);
	dy = abs((int)end.y - (int)start.y);
	if (dx > dy)
		return (dx);
	else
		return (dy);
}
