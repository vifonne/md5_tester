/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:33:21 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/08 00:02:48 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*srce;

	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	if (dest < srce)
	{
		while (len)
		{
			*dest++ = *srce++;
			len--;
		}
	}
	else
	{
		while (len)
		{
			*(dest + len - 1) = *(srce + len - 1);
			len--;
		}
	}
	return (dst);
}
