/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:06:41 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/02/07 16:56:43 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include "libft.h"
#include "keys.h"

static int	is_available(int key)
{
	if (key == PAD_1 || key == PAD_2 || key == PAD_3 || key == PAD_4
			|| key == PAD_6 || key == PAD_7 || key == PAD_8 || key == PAD_9
			|| key == A || key == W || key == S || key == D || key == Q
			|| key == E || key == M || key == Z || key == X || key == SPACE
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

int			key_press(int key, t_fdf *fdf)
{
	static int	printed = 0;

	if (!is_available(key))
		return (0);
	if (key == ESC)
		red_cross_closing(fdf);
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
	if (key == A || key == W || key == S || key == D || key == Q || key == E
			|| key == Z || key == X)
		event_move(key, fdf);
	else if (key == SPACE)
		event_reset(fdf);
	else if (key == PLUS || key == MINUS || key == PAD_PLUS || key == PAD_MINUS)
		event_zoom(key, &(fdf->map_info));
	else if (key == UP_ARROW || key == DOWN_ARROW || key == PAD_1
			|| key == PAD_2 || key == PAD_3 || key == PAD_4 || key == PAD_6
			|| key == PAD_7 || key == PAD_8 || key == PAD_9)
	{
		if (key == UP_ARROW || key == DOWN_ARROW)
			event_adjust_alt(key, &(fdf->map_info));
		else
			event_move(key, fdf);
		if(!(projection(fdf)))
			error("error: failed to update projection", fdf);
	}
	else if (key == R)
	{
		COLOR_SCHEME = FANCY_RAINBOW;
		event_rainbow(fdf);
	}
	draw_image(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	if (key == M)
	{
		if (printed == 0)
		{
			printed = 1;
			command_menu(*fdf);
		}
		else
		{
			printed = 0;
			mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
		}
	}
	return (0);
}

int			key_release(int key, t_fdf *fdf)
{
	if (key == P || key == I || key == T || key == C)
	{
		ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * 4);
//		event_reset(fdf);
		if (key == P)
			PROJ = PARALLEL;
		if (key == I)
			PROJ = ISOMETRIC;
		if (key == T)
			PROJ = TOP;
		if (key == C)
		{
			COLOR_SCHEME = (COLOR_SCHEME == MONO) ? ALTITUDE : COLOR_SCHEME + 1;
			COLOR_SCHEME += (COLOR_SCHEME == FANCY_RAINBOW) ? 1 : 0;
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
