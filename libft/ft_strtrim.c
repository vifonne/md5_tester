/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:05:22 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/08 14:59:32 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static size_t	ft_len(char const *s)
{
	size_t	i;
	size_t	n;
	char	*str;

	i = 0;
	n = 0;
	if (!(str = ft_strdup(s)))
		return (-1);
	while (ft_isblank(*str) == 1 && *str)
		str++;
	while (str[i])
	{
		while (ft_isblank(str[i + n]) == 1 && str[i + n])
			n++;
		if (str[i + n] == '\0')
			return (i);
		else
			n = 0;
		i++;
	}
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	if (s)
	{
		len = ft_len(s);
		if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i] != '\0')
			i++;
		str = (char *)ft_memmove((void *)str, (const void *)(s + i), len);
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}
