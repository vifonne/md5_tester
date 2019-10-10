/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 21:03:31 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/07 19:10:49 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = ft_strlen(s1);
	if (n <= ft_strlen(s2))
	{
		ft_memmove(s1 + len, s2, n);
		s1[len + n] = '\0';
		return (s1);
	}
	ft_memmove(s1 + len, s2, ft_strlen(s2));
	s1[len + ft_strlen(s2)] = '\0';
	return (s1);
}
