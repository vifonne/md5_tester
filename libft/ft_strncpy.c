/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:12:36 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/07 23:11:05 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	if (ft_strcmp(src, "") == 0)
		ft_bzero(dst, len);
	ft_memmove(dst, src, len);
	if (ft_strlen(src) < len)
		ft_bzero(dst + ft_strlen(src), len - ft_strlen(src));
	return (dst);
}
