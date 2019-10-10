/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:47:11 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/07 18:42:28 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*srce;
	unsigned char	cc;

	cc = (unsigned char)c;
	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	while (n > 0)
	{
		if (*srce == cc)
		{
			*dest = cc;
			return (++dest);
		}
		*dest++ = *srce++;
		n--;
	}
	return (NULL);
}
