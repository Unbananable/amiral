/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/28 17:10:20 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>

static int	is_available(int key)
{
	if (key == A || key == W || key == S || key == D || key == Q || key == E
			|| key == Z || key == X || key == SPACE || key == PLUS
			|| key == MINUS || key == NUMPAD_PLUS || key == NUMPAD_MINUS
			|| key == UP_ARROW || key == DOWN_ARROW)
		return (1);
	return (0);
}

int			red_cross_closing(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int			key_press(int key, t_fdf *fdf)
{
	if (!is_available(key))
		return (0);
	if (key == ESC)
		exit(0);
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
	if (key == A || key == W || key == S || key == D || key == Q || key == E
			|| key == Z || key == X)
		event_move(key, &(fdf->map_info));
	else if (key == SPACE)
		get_placement_info(fdf->proj_map, &(fdf->map_info));
	else if (key == PLUS || key == MINUS || key == NUMPAD_PLUS
			|| key == NUMPAD_MINUS)
		event_zoom(key, &(fdf->map_info));
	if (key == UP_ARROW || key == DOWN_ARROW)
		event_adjust_alt(key, &(fdf->map_info));
	draw_img(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	return (0);
}

int			key_release(int key, t_fdf *fdf)
{
	if (key == P || key == I || key == T)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
		if (key == P)
			fdf->proj_map = projection(PARALLEL, fdf->map, &(fdf->map_info));
		if (key == I)
			fdf->proj_map = projection(ISOMETRIC, fdf->map, &(fdf->map_info));
		if (key == T)
			fdf->proj_map = projection(TOP, fdf->map, &(fdf->map_info));
		get_placement_info(fdf->proj_map, &(fdf->map_info));
		draw_img(fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}