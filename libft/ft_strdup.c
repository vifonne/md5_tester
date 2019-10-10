/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:53:25 by vifonne           #+#    #+#             */
/*   Updated: 2018/12/18 13:35:41 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (s1)
	{
		while (s1[i])
			i++;
		if (!(s2 = (char *)malloc(sizeof(char) * (i + 1))))
			exit(0);
		ft_memcpy(s2, s1, i);
		s2[i] = '\0';
		return (s2);
	}
	return (NULL);
}
