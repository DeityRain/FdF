/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:48:09 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/28 15:18:03 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_zoom(int button, t_fdf *fdf)
{
	if (button == 4)
	{
		fdf->camera->zoom *= 1.1;
		if (fdf->camera->zoom > 200)
			fdf->camera->zoom = 200;
		draw_map(fdf);
	}
	else if (button == 5)
	{
		fdf->camera->zoom /= 1.1;
		if (fdf->camera->zoom < 1)
			fdf->camera->zoom = 1;
		draw_map(fdf);
	}
}

int	mouse_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->mouse.is_pressed = 1;
		fdf->mouse.prev_x = x;
		fdf->mouse.prev_y = y;
	}
	else if (button == 2)
	{
		fdf->mouse.is_pressed = 2;
		fdf->mouse.prev_x = x;
		fdf->mouse.prev_y = y;
	}
	else
		handle_zoom(button, fdf);
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)button;
	(void)x;
	(void)y;
	fdf->mouse.is_pressed = 0;
	return (0);
}

static void	handle_rotation(int x, int y, t_fdf *fdf)
{
	int			dx;
	int			dy;
	static int	skip_frames = 0;

	skip_frames++;
	if (skip_frames % 2 == 0)
		return ;
	dx = x - fdf->mouse.prev_x;
	dy = y - fdf->mouse.prev_y;
	fdf->camera->gamma -= dx * 0.005;
	fdf->camera->alpha -= dy * 0.005;
	fdf->mouse.prev_x = x;
	fdf->mouse.prev_y = y;
	draw_map(fdf);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	int	dx;
	int	dy;

	if (fdf->mouse.is_pressed == 1)
		handle_rotation(x, y, fdf);
	else if (fdf->mouse.is_pressed == 2)
	{
		dx = x - fdf->mouse.prev_x;
		dy = y - fdf->mouse.prev_y;
		fdf->camera->x_offset += dx;
		fdf->camera->y_offset += dy;
		fdf->mouse.prev_x = x;
		fdf->mouse.prev_y = y;
		draw_map(fdf);
	}
	return (0);
}
