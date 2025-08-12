/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:22 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/29 07:44:12 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	rotate_x(t_point point, float angle)
{
	t_point	rotated;
	float	y;
	float	z;

	y = point.y;
	z = point.z;
	rotated.x = point.x;
	rotated.y = y * cos(angle) - z * sin(angle);
	rotated.z = y * sin(angle) + z * cos(angle);
	rotated.color = point.color;
	return (rotated);
}

t_point	rotate_y(t_point point, float angle)
{
	t_point	rotated;
	float	x;
	float	z;

	x = point.x;
	z = point.z;
	rotated.x = x * cos(angle) + z * sin(angle);
	rotated.y = point.y;
	rotated.z = -x * sin(angle) + z * cos(angle);
	rotated.color = point.color;
	return (rotated);
}

t_point	rotate_z(t_point point, float angle)
{
	t_point	rotated;
	float	x;
	float	y;

	x = point.x;
	y = point.y;
	rotated.x = x * cos(angle) - y * sin(angle);
	rotated.y = x * sin(angle) + y * cos(angle);
	rotated.z = point.z;
	rotated.color = point.color;
	return (rotated);
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		*(unsigned int *)(fdf->addr + (y * fdf->line_length + x
					* (fdf->bits_per_pixel / 8))) = color;
}
