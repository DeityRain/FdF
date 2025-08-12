/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 07:41:34 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/22 09:48:46 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_altitude_color(int z, int z_min, int z_max)
{
	double	percent;
	int		r;
	int		g;
	int		b;

	if (z_max == z_min)
		return (0x00FF00);
	percent = (double)(z - z_min) / (double)(z_max - z_min);
	if (percent < 0.5)
	{
		r = (int)(255 * (percent * 2));
		g = (int)(255 * (percent * 2));
		b = 255;
	}
	else
	{
		r = 255;
		g = (int)(255 * (1 - (percent - 0.5) * 2));
		b = (int)(255 * (1 - (percent - 0.5) * 2));
	}
	return ((r << 16) | (g << 8) | b);
}
