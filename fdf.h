/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:55:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/27 17:37:49 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "keys.h"

# define WIN_HEIGHT 1200
# define WIN_WIDTH 1200
# define MARGIN 100
# define BUFFER_SIZE 100

# define WIDTH map_info->width
# define DEPTH map_info->depth
# define XMIN map_info->xmin
# define XMAX map_info->xmax
# define YMIN map_info->ymin
# define YMAX map_info->ymax
# define SCALE map_info->scale


typedef struct	s_point
{
	double	x;
	double	y;
	int		colour;
}				t_point;

typedef struct	s_map
{
	int		width;
	int		depth;
	double	xmax;
	double	xmin;
	double	ymax;
	double	ymin;
	double	scale;
	int		x_offset;
	int		y_offset;
	double	zmax;
	double	zmin;
}				t_map;

typedef struct	s_image
{
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_fdf
{
	unsigned int	*addr;
	int		**map;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	t_point	**proj_map;
	t_map	map_info;
	t_image	image;
}				t_fdf;

void	fill_pixel(t_fdf *fdf, t_point p);
void	new_image(t_fdf *fdf);
void	draw_img(t_fdf *fdf, t_point **points, t_map map_info);
t_image	delete_image(t_fdf *fdf, t_image *image);
void	clear_image(t_fdf * fdf);

void	error(char *str);
void	draw_line(t_fdf *fdf, t_point p0, t_point p1, t_map map_info);
void	draw(t_fdf *fdf, t_point **points, t_map map_info);
int		**reader(char *file_name, t_map *map_info);
t_point	**parallel_projection(int**map, t_map *map_info);
t_point	**isometric_projection(int **map, t_map *map_info);
t_point **top_projection(int **map, t_map *map_info);
void	get_placement_info(t_point **proj_map, t_map *map_info);

int		red_cross_closing(void *param);
int		mouse_press(int button, int x, int y, t_fdf *fdf);
int		mouse_release(int button, int x, int y, t_fdf *fdf);
int		key_press(int key, t_fdf *fdf);
int		key_release(int key, t_fdf *fdf);

#endif
