/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:02:07 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/29 07:44:49 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham_step(t_bresenham *b)
{
	b->e2 = 2 * b->err;
	if (b->e2 > -b->dy)
	{
		b->err -= b->dy;
		b->x += b->sx;
	}
	if (b->e2 < b->dx)
	{
		b->err += b->dx;
		b->y += b->sy;
	}
}

void	init_bresenham(t_bresenham *b, t_point start, t_point end)
{
	b->dx = abs((int)end.x - (int)start.x);
	b->dy = abs((int)end.y - (int)start.y);
	b->sx = get_sign((int)start.x, (int)end.x);
	b->sy = get_sign((int)start.y, (int)end.y);
	b->err = b->dx - b->dy;
	b->x = (int)start.x;
	b->y = (int)start.y;
}

void	draw_line(t_fdf *fdf, t_point start, t_point end)
{
	t_bresenham	b;
	int			current_step;
	int			total_steps;
	int			color;
	float		color_ratio;

	init_bresenham(&b, start, end);
	total_steps = calculate_line_distance(start, end);
	current_step = 0;
	while (b.x != (int)end.x || b.y != (int)end.y)
	{
		color_ratio = 0.0;
		if (total_steps > 0)
			color_ratio = (float)current_step / (float)total_steps;
		color = interpolate_color(start.color, end.color, color_ratio);
		put_pixel(fdf, b.x, b.y, color);
		bresenham_step(&b);
		current_step++;
	}
	put_pixel(fdf, b.x, b.y, end.color);
}

t_point	project_iso(t_point point, t_fdf *fdf)
{
	t_point	projected;
	float	prev_x;
	float	prev_y;

	point = rotate_x(point, fdf->camera->alpha);
	point = rotate_y(point, fdf->camera->beta);
	point = rotate_z(point, fdf->camera->gamma);
	prev_x = point.x;
	prev_y = point.y;
	projected.x = (prev_x - prev_y) * cos(0.523599);
	projected.y = (prev_x + prev_y) * sin(0.523599) - point.z;
	projected.x = projected.x * fdf->camera->zoom + fdf->camera->x_offset;
	projected.y = projected.y * fdf->camera->zoom + fdf->camera->y_offset;
	projected.z = point.z;
	projected.color = point.color;
	return (projected);
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_horizontal(fdf, x, y);
			if (y < fdf->map->height - 1)
				draw_vertical(fdf, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
