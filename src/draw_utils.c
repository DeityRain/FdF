/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:56:03 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/29 06:51:29 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_fdf *fdf)
{
	int	i;
	int	total;

	total = WIN_HEIGHT * WIN_WIDTH;
	i = 0;
	while (i < total)
	{
		((int *)fdf->addr)[i] = 0x000000;
		i++;
	}
}

int	get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

t_point	get_point(t_map *map, int x, int y)
{
	t_point	point;

	point.x = x - map->width / 2.0;
	point.y = y - map->height / 2.0;
	point.z = map->z_matrix[y][x];
	if (map->colors && map->colors[y][x])
		point.color = map->colors[y][x];
	else
	{
		if (point.z == 0)
			point.color = CYAN;
		else if (point.z > 0)
			point.color = YELLOW;
		else
			point.color = PINK;
	}
	return (point);
}

void	draw_horizontal(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = get_point(fdf->map, x, y);
	p2 = get_point(fdf->map, x + 1, y);
	if (fdf->camera->color_mode == 1)
	{
		p1.color = get_altitude_color(p1.z, fdf->map->z_min, fdf->map->z_max);
		p2.color = get_altitude_color(p2.z, fdf->map->z_min, fdf->map->z_max);
	}
	p1 = project_iso(p1, fdf);
	p2 = project_iso(p2, fdf);
	draw_line(fdf, p1, p2);
}

void	draw_vertical(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = get_point(fdf->map, x, y);
	p2 = get_point(fdf->map, x, y + 1);
	if (fdf->camera->color_mode == 1)
	{
		p1.color = get_altitude_color(p1.z, fdf->map->z_min, fdf->map->z_max);
		p2.color = get_altitude_color(p2.z, fdf->map->z_min, fdf->map->z_max);
	}
	p1 = project_iso(p1, fdf);
	p2 = project_iso(p2, fdf);
	draw_line(fdf, p1, p2);
}
