/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:07:41 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/01 17:53:41 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_parse_tmp(char *save, char **line)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(save, 10)))
	{
		*tmp = 0;
		if (!(tmp = ft_strdup(tmp + 1)))
			return (NULL);
		if (!(*line = ft_strdup(save)))
			return (NULL);
		ft_strdel(&save);
		save = tmp;
	}
	else
	{
		if (!(*line = ft_strdup(save)))
			return (NULL);
		ft_strclr(save);
	}
	return (save);
}

int		ft_strrdel(int ret, char *save)
{
	ft_strdel(&save);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char		*save;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || !line || read(fd, 0, 0) < 0)
		return (-1);
	if (!save && !(save = ft_strnew(0)))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (ret);
		buf[ret] = '\0';
		if (!(save = ft_strdjoin(save, buf)))
			return (-1);
		if (ft_strchr(buf, 10))
			break ;
	}
	if (ret <= 0 && !(*save))
		return (ret);
	if (!(save = ft_parse_tmp(save, line)))
		return (ft_strrdel(ret, save));
	return (1);
}
