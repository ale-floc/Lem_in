/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramos <anramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 00:05:34 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/09 19:05:58 by anramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		get_read(int fd, char **ret)
{
	int		c;
	char	*tmp;
	char	*buf;

	c = BUFF_SIZE;
	buf = ft_strnew(BUFF_SIZE + 1);
	while ((ft_strchr(*ret, '\n') == NULL) && c == BUFF_SIZE)
	{
		c = read(fd, buf, BUFF_SIZE);
		buf[c] = '\0';
		tmp = ft_strjoin(*ret, buf);
		free(*ret);
		*ret = ft_strdup(tmp);
		free(tmp);
	}
	free(buf);
	return (c);
}

int		get_next_line(int const fd, char **line)
{
	static char	*ret[256];
	char		*tmp;
	int			c;

	if (fd < 0 || !line)
		return (-1);
	if (!ret[fd])
		ret[fd] = ft_strnew(0);
	if ((c = get_read(fd, &ret[fd])) == -1)
		return (-1);
	if (c < BUFF_SIZE && ft_strchr(ret[fd], '\n') == NULL)
	{
		if (ft_strlen(*line) == 0)
			return (0);
		*line = ft_strdup(ret[fd]);
		ft_strclr(ret[fd]);
		return (ft_strlen(*line) == 0 ? 0 : 1);
	}
	*line = ft_strsub(ret[fd], 0, (size_t)(ft_strchr(ret[fd], '\n') - ret[fd]));
	tmp = ft_strdup(ft_strchr(ret[fd], '\n') + 1);
	free(ret[fd]);
	ret[fd] = ft_strdup(tmp);
	free(tmp);
	return (ft_strlen(*line) == 0 ? 0 : 1);
}
