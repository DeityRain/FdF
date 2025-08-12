/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <qdeffaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:00:00 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/08/05 08:17:19 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(char *msg)
{
	ft_printf("Error: %s\n", msg);
	exit(1);
}

static void	setup_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 0, handle_close, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, handle_key, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 1L << 3, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 1L << 6, mouse_move, fdf);
}

static int	validate_file(char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		ft_printf("Error: File must have .fdf extension\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static t_fdf	*init_components(char *filename)
{
	t_fdf	*fdf;

	if (!validate_file(filename))
		error_exit("Failed to open file");
	fdf = init_fdf();
	fdf->map = init_map(filename);
	if (!fdf->map)
	{
		cleanup_mlx(fdf);
		free(fdf);
		error_exit("Failed to load map");
	}
	fdf->camera = init_camera();
	if (!fdf->camera)
	{
		cleanup_fdf(fdf);
		error_exit("Failed to initialize camera");
	}
	return (fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf map.fdf\n");
		return (1);
	}
	ft_printf("Loading map: %s\n", argv[1]);
	fdf = init_components(argv[1]);
	setup_hooks(fdf);
	draw_map(fdf);
	ft_printf("FdF ready! Press ESC to exit.\n");
	mlx_loop(fdf->mlx);
	return (0);
}
