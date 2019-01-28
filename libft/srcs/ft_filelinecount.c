/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filelinecount.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:18:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/28 17:30:41 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

int		ft_filelinecount(char *path)
{
	int		nblines;
	int		readchar;
	char	buf[4097];
	int		i;
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	nblines = 0;
	while ((readchar = read(fd, buf, 4096)) > 0)
	{
		buf[readchar] = 0;
		i = 0;
		while (i < readchar)
		{
			if (buf[i] == '\n')
				nblines++;
			i++;
		}
	}
	close(fd);
	return (nblines);
}
