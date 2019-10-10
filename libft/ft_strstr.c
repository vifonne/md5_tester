/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:33:06 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/15 14:24:55 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	n;
	char	*h_stack;

	i = 0;
	n = 0;
	h_stack = (char *)haystack;
	if (ft_strcmp(needle, "") == 0)
		return (h_stack);
	while (h_stack[i])
	{
		while (needle[n] && h_stack[i + n] == needle[n])
			n++;
		if (n != ft_strlen(needle))
			n = 0;
		else
			return (h_stack + i);
		i++;
	}
	return (NULL);
}
