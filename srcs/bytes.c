/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:38:44 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 15:19:13 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <stdio.h>

uint32_t	bswap_32(uint32_t bytes)
{
	bytes = ((bytes >> 24) & 0xFF)
		| ((bytes << 8) & 0xFF0000)
		| ((bytes >> 8) & 0xFF00)
		| ((bytes << 24) & 0xFF000000);
	return (bytes);
}

uint64_t	bswap_64(uint64_t bytes)
{
	bytes = (bytes & 0x00000000FFFFFFFF) << 32
		| (bytes & 0xFFFFFFFF00000000) >> 32;
	bytes = (bytes & 0x0000FFFF0000FFFF) << 16
		| (bytes & 0xFFFF0000FFFF0000) >> 16;
	bytes = (bytes & 0x00FF00FF00FF00FF) << 8
		| (bytes & 0xFF00FF00FF00FF00) >> 8;
	return (bytes);
}

void		print_byte(t_msg *msg)
{
	uint8_t		to_print[32];
	uint32_t	tmp;
	int			idx;
	int			size;

	idx = 0;
	size = 16;
	if (msg->algo_choosen == 1)
	{
		size = sizeof(uint32_t) * 8;
		while (idx < 8)
		{
			tmp = bswap_32(msg->md_buffer.h[idx]);
			ft_memcpy(to_print + idx * sizeof(uint32_t), &tmp, sizeof(uint32_t));
			idx++;
		}
		idx = 0;
	}
	else
		ft_memcpy(to_print, msg->md_buffer.h, size);
	while (idx < size)
	{
		printf("%02x", to_print[idx]);
		idx++;
	}
	fflush(stdout);
}
