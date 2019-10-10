/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:22:09 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/07 18:08:10 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		tmp;
	char	*str;

	str = (char *)s;
	i = 0;
	tmp = -1;
	if (c == 0)
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (char)c)
			tmp = i;
		i++;
	}
	if (tmp == -1)
		return (NULL);
	return (str + tmp);
}
