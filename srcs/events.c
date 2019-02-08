/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/08 12:23:46 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include "libft.h"
#include "keys.h"

static int	is_available(int key)
{
	if (DIR_KEYS || PAD_NBRS || key == M || key == SPACE
			|| key == PLUS || key == MINUS || key == PAD_PLUS
			|| key == PAD_MINUS || key == UP_ARROW || key == DOWN_ARROW
			|| key == ESC || key == R)
		return (1);
	return (0);
}

int			red_cross_closing(t_fdf *fdf)
{
	clear_fdf(fdf);
	exit(0);
	return (0);
}

static void	menu_and_escape(int key, t_fdf *fdf)
{
	if (key == M)
		print_command_menu(*fdf);
	if (key == ESC)
		red_cross_closing(fdf);
}

int			key_press(int key, t_fdf *fdf)
{
	if (!is_available(key))
		return (0);
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
	if (DIR_KEYS)
		event_move(key, fdf);
	else if (key == SPACE)
		event_reset(fdf);
	else if (key == PLUS || key == MINUS || key == PAD_PLUS || key == PAD_MINUS)
		event_zoom(key, fdf);
	else if (key == UP_ARROW || key == DOWN_ARROW || PAD_NBRS)
	{
		if (key == UP_ARROW || key == DOWN_ARROW)
			event_adjust_alt(key, fdf);
		else
			event_move(key, fdf);
		if (!(projection(fdf)))
			error("error: failed to update projection", fdf);
	}
	else if (key == R)
	{
		fdf->color_scheme = FANCY_RAINBOW;
		event_rainbow(fdf);
	}
	draw_image(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	menu_and_escape(key, fdf);
	return (0);
}

int			key_release(int key, t_fdf *fdf)
{
	if (key == P || key == I || key == T || key == C)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
		if (key == P)
			fdf->proj_type = PARALLEL;
		if (key == I)
			fdf->proj_type = ISOMETRIC;
		if (key == T)
			fdf->proj_type = TOP;
		if (key == C)
		{
			fdf->color_scheme = (fdf->color_scheme == MONO) ? ALTITUDE : fdf->color_scheme + 1;
			fdf->color_scheme += (fdf->color_scheme == FANCY_RAINBOW) ? 1 : 0;
		}
		else
		{
			if (!projection(fdf))
				error("error: failed to update projection", fdf);
			get_placement_info(fdf);
		}
		draw_image(fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	return (0);
}
