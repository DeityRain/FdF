/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:58:10 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/08/05 08:03:36 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* System includes */
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

/* Local includes */
# include "libft.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"

/* Window dimensions */
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

/* Colors */
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BLACK 0x0F0F0F
# define CYAN 0x008B8B
# define PINK 0xFF1493
# define YELLOW 0xFFD700

/* Structures */
typedef struct s_color_rgb
{
	int			r;
	int			g;
	int			b;
}				t_color_rgb;

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int			color;
}				t_point;

typedef struct s_map
{
	int			**z_matrix;
	int			**colors;
	int			width;
	int			height;
	int			z_min;
	int			z_max;
}				t_map;

typedef struct s_camera
{
	float		zoom;
	float		x_offset;
	float		y_offset;
	float		alpha;
	float		beta;
	float		gamma;
	int			projection;
	int			color_mode;
}				t_camera;

typedef struct s_mouse
{
	int			is_pressed;
	int			prev_x;
	int			prev_y;
}				t_mouse;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
	t_camera	*camera;
	t_mouse		mouse;
}				t_fdf;

typedef struct s_bresenham
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			x;
	int			y;
}				t_bresenham;

/* main.c */
void			error_exit(char *msg);

/* init.c */
t_fdf			*init_fdf(void);
t_camera		*init_camera(void);
t_map			*init_map(char *filename);
void			find_min_max(t_map *map);
int				check_file_extension(char *filename);

/* fdf_parser.c */
int				**parse_map(char *filename, int *width, int *height);
void			get_map_dimensions(char *filename, int *width, int *height);
int				**allocate_map(int width, int height);
void			fill_map(char *filename, int **map, int width, int height);

/* parser_utils.c */
void			free_split(char **split);
int				parse_value(char *str);

/* draw.c */
void			bresenham_step(t_bresenham *b);
void			init_bresenham(t_bresenham *b, t_point start, t_point end);
void			draw_map(t_fdf *fdf);
void			draw_line(t_fdf *fdf, t_point start, t_point end);
t_point			project_iso(t_point point, t_fdf *fdf);

/* draw_utils.c */
void			clear_image(t_fdf *fdf);
int				get_sign(int a, int b);
t_point			get_point(t_map *map, int x, int y);
void			draw_horizontal(t_fdf *fdf, int x, int y);
void			draw_vertical(t_fdf *fdf, int x, int y);

/* color_utils.c */
t_color_rgb		get_rgb(int color);
int				create_color(int r, int g, int b);
int				interpolate_color(int start_color, int end_color, float ratio);
int				calculate_line_distance(t_point start, t_point end);

/* transform.c */
t_point			rotate_x(t_point point, float angle);
t_point			rotate_y(t_point point, float angle);
t_point			rotate_z(t_point point, float angle);
void			put_pixel(t_fdf *fdf, int x, int y, int color);

/* events.c */
int				handle_key(int keycode, t_fdf *fdf);
int				handle_close(t_fdf *fdf);

/* mouse.c */
int				mouse_press(int button, int x, int y, t_fdf *fdf);
int				mouse_release(int button, int x, int y, t_fdf *fdf);
int				mouse_move(int x, int y, t_fdf *fdf);

/* color.c */
int				get_altitude_color(int z, int z_min, int z_max);

/* cleanup.c */
void			free_map(int **map, int height);
void			cleanup_fdf(t_fdf *fdf);
void			cleanup_map(t_map *map);
void			cleanup_mlx(t_fdf *fdf);

#endif
