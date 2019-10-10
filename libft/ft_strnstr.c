/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 20:33:06 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/15 14:25:06 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	n;
	char	*h_stack;

	i = 0;
	n = 0;
	h_stack = (char *)haystack;
	if (!ft_strlen(needle))
		return (h_stack);
	while (h_stack[i])
	{
		while (needle[n] && h_stack[i + n] == needle[n])
		{
			n++;
			if (i + n > len)
				return (NULL);
		}
		if (n != ft_strlen(needle) && n + i++ < len)
			n = 0;
		else if (i + n <= len)
			return (h_stack + i);
		else
			i++;
	}
	return (NULL);
}
