/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:55:15 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/22 14:24:14 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_movement_keys(int keycode, t_fdf *fdf)
{
	if (keycode == 126 || keycode == 65362)
		fdf->camera->y_offset -= 30;
	else if (keycode == 125 || keycode == 65364)
		fdf->camera->y_offset += 30;
	else if (keycode == 123 || keycode == 65361)
		fdf->camera->x_offset -= 30;
	else if (keycode == 124 || keycode == 65363)
		fdf->camera->x_offset += 30;
}

static void	handle_zoom_keys(int keycode, t_fdf *fdf)
{
	if (keycode == 69 || keycode == 61)
		fdf->camera->zoom += 5;
	else if (keycode == 78 || keycode == 45)
		fdf->camera->zoom -= 5;
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
}

static void	handle_rotation_keys(int keycode, t_fdf *fdf)
{
	if (keycode == 13 || keycode == 119)
		fdf->camera->alpha += 0.1;
	else if (keycode == 1 || keycode == 115)
		fdf->camera->alpha -= 0.1;
	else if (keycode == 0 || keycode == 97)
		fdf->camera->beta += 0.1;
	else if (keycode == 2 || keycode == 100)
		fdf->camera->beta -= 0.1;
	else if (keycode == 12 || keycode == 113)
		fdf->camera->gamma += 0.1;
	else if (keycode == 14 || keycode == 101)
		fdf->camera->gamma -= 0.1;
}

int	handle_key(int keycode, t_fdf *fdf)
{
	ft_printf("Key pressed: %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
		handle_close(fdf);
	handle_movement_keys(keycode, fdf);
	handle_zoom_keys(keycode, fdf);
	handle_rotation_keys(keycode, fdf);
	if (keycode == 8 || keycode == 99)
	{
		fdf->camera->color_mode = !fdf->camera->color_mode;
		if (fdf->camera->color_mode)
			ft_printf("Color mode: Altitude\n");
		else
			ft_printf("Color mode: Default\n");
	}
	draw_map(fdf);
	return (0);
}

int	handle_close(t_fdf *fdf)
{
	cleanup_fdf(fdf);
	exit(0);
	return (0);
}
