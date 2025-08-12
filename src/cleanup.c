/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:55:40 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/30 11:28:15 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(int **map, int height)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	if (map->z_matrix)
		free_map(map->z_matrix, map->height);
	if (map->colors)
		free_map(map->colors, map->height);
	free(map);
}

void	cleanup_mlx(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
}

void	cleanup_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	cleanup_map(fdf->map);
	if (fdf->camera)
		free(fdf->camera);
	cleanup_mlx(fdf);
	free(fdf);
}
