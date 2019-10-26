/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:29:05 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/26 16:45:30 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <stdio.h>

size_t	md5_padding_calc(t_msg *msg)
{
	size_t	to_add;

	to_add = 0;
	if (msg->length >= 56 && msg->length < 64)
	{
		msg->length += 64 - msg->length;
		to_add = 64 - msg->length;
	}
	if (msg->length < 64)
		to_add += 56 - msg->length ;
	else
		to_add += msg->length + 56 - (msg->length % 64) - msg->length;
	return (to_add);
}

int		md5_append_padding(t_msg *msg)
{
	size_t	to_add;
	uint8_t	*tmp;

	if (!(tmp = (uint8_t *)ft_memalloc(msg->length + 1)))
		return (0);
	ft_memcpy(tmp, msg->buffer, msg->length);
	*(tmp + msg->length) = 1 << 7;
	msg->length += 1;
	to_add = md5_padding_calc(msg);
	if (!(msg->buffer_prepared = (uint8_t *)ft_memalloc(msg->length + to_add)))
		return (0);
	msg->length += to_add;
	ft_memcpy(msg->buffer_prepared, tmp, msg->length);
	free(tmp);
	return (1);
}

int		md5_append_length(t_msg *msg)
{
	uint8_t	*tmp;

	if (!(tmp = (uint8_t *)ft_memalloc(msg->length + sizeof(uint64_t))))
		return (0);
	ft_memcpy(tmp, msg->buffer_prepared, msg->length);
	printf("len: %zu\n", msg->length);
	*(uint64_t *)(tmp + msg->length) = (uint64_t)(msg->content_original_len * 8);
	free(msg->buffer_prepared);
	msg->buffer_prepared = tmp;
	msg->length += sizeof(uint64_t);
	return (1);
}

void	md5_init_md_buffer(t_msg *msg)
{
	msg->md_buffer.h[0] = 0x67452301;
	msg->md_buffer.h[1] = 0xEFCDAB89;
	msg->md_buffer.h[2] = 0x98BADCFE;
	msg->md_buffer.h[3] = 0x10325476;
}

int		md5_preparation(t_msg *msg)
{
	msg->length = msg->content_original_len;
	if (!md5_append_padding(msg)
			|| !md5_append_length(msg))
		return (0);
	return (1);
}
