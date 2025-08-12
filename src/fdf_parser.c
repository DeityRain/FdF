/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:34:36 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/22 14:34:51 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	count_width(char *line, int *width)
{
	char	**split;

	split = ft_split(line, ' ');
	*width = 0;
	while (split[*width])
		(*width)++;
	free_split(split);
}

void	get_map_dimensions(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	int		first_row;

	first_row = 1;
	*height = 0;
	*width = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Can't open file");
	line = get_next_line(fd);
	while (line)
	{
		if (first_row)
		{
			count_width(line, width);
			first_row = 0;
		}
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("Map dimension: %d x %d\n", *width, *height);
}

int	**allocate_map(int width, int height)
{
	int	**map;
	int	i;

	map = (int **)ft_calloc(height, sizeof(int *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (int *)ft_calloc(width, sizeof(int));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

void	fill_map(char *filename, int **map, int width, int height)
{
	int		fd;
	char	*line;
	char	**split;
	int		row;
	int		col;

	row = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line && row < height)
	{
		split = ft_split(line, ' ');
		col = -1;
		while (++col < width && split[col])
			map[row][col] = parse_value(split[col]);
		free_split(split);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
}

int	**parse_map(char *filename, int *width, int *height)
{
	int	**map;

	get_map_dimensions(filename, width, height);
	if (*width <= 0 || *height <= 0)
	{
		ft_printf("Error: Invalid map dimension\n");
		return (NULL);
	}
	map = allocate_map(*width, *height);
	if (!map)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	fill_map(filename, map, *width, *height);
	return (map);
}
