/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 01:15:11 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/02 17:26:05 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_nstr(char const *str, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
			i++;
		n++;
	}
	return (n + 1);
}

static size_t	ft_strclen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i + 1);
}

static size_t	ft_m_strcpy(char *dst, const char *src, char c)
{
	size_t	j;

	j = 0;
	while (src[j] && src[j] != c)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (j);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	k;
	char	**tab;

	k = 0;
	i = 0;
	if (!s || !(tab = (char **)malloc(sizeof(char *) * ft_nstr(s, c))))
		return (NULL);
	while (s[k])
	{
		while (s[k] == c && s[k])
			k++;
		if (s[k] == '\0')
			break ;
		if (!(tab[i] = (char *)malloc(sizeof(char) * ft_strclen((s + k), c))))
			return (NULL);
		k += ft_m_strcpy(tab[i], (s + k), c);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
