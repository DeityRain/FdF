/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:55:04 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/08/05 08:03:07 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_file_extension(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".fdf", 4) != 0)
		return (0);
	return (1);
}

t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		error_exit("Failed to allocate FdF structure");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		error_exit("Failed to initialize MLX");
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF - 42");
	if (!fdf->win)
		error_exit("Failed to create window");
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		error_exit("Failed to create image");
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	fdf->mouse.is_pressed = 0;
	fdf->mouse.prev_x = 0;
	fdf->mouse.prev_y = 0;
	return (fdf);
}

t_camera	*init_camera(void)
{
	t_camera	*camera;

	camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->zoom = 20;
	camera->x_offset = WIN_WIDTH / 2;
	camera->y_offset = WIN_HEIGHT / 2;
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->projection = 0;
	camera->color_mode = 0;
	return (camera);
}

t_map	*init_map(char *filename)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->z_matrix = parse_map(filename, &(map->width), &(map->height));
	if (!map->z_matrix)
	{
		free(map);
		return (NULL);
	}
	map->colors = NULL;
	find_min_max(map);
	return (map);
}

void	find_min_max(t_map *map)
{
	int	row;
	int	col;

	map->z_min = map->z_matrix[0][0];
	map->z_max = map->z_matrix[0][0];
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (map->z_matrix[row][col] < map->z_min)
				map->z_min = map->z_matrix[row][col];
			if (map->z_matrix[row][col] > map->z_max)
				map->z_max = map->z_matrix[row][col];
			col++;
		}
		row++;
	}
	ft_printf("Height range: %d to %d\n", map->z_min, map->z_max);
}
